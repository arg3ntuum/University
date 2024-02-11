/*��� 4. ��������� SQL ������, �� ��������� ������� 䳿:
1 ������ ��������� ��� �������, �� ���������, � ���� ����� �������� � ������� groups � ������������� ������� ALTER TABLE.
2 ������� �� ����� �.�.�. (������� - �������, ��'� �� �� ������� - ���������) 
				��� ��������, �� ������ � ����������.
3 ������� �� ����� �.�.�. (������� - �������, ��'� �� �� ������� - ���������) 
				��� �������������'������ �������� (�������, 18<= �� < 25, ������� �� �������� ������).
4 ������� �� ����� �.�.�. (������� - �������, ��'� �� �� ������� - ���������) 
				� � ����� ��� ��������, ��
5 ������� �� ����� �.�.�. (������� - �������, ��'� �� �� ������� - ���������) 
				� ����� ��� ��������, �� ����� �������� ����� (����� �� ����), � ����� ����� ��� ���������� ����� � �� ��� (������ ��� ����).
6 ������� ������ �������� � ������ �� ��� ��� ����������� �������� (������� ���������� �� ������ �������).
7 �������������� common table expressions �������� ������� ���: ����� ��������, ��� ������������, ����� �����.
*/

--���������� �������
SELECT * FROM [Lab_2].[dbo].[ArticleStudentAssociation];
SELECT * FROM [Lab_2].[dbo].[ArticleProfessorsAssociation];
SELECT * FROM [Lab_2].[dbo].[Articles];
SELECT * FROM [Lab_2].[dbo].[ConferencePapers];
SELECT * FROM [Lab_2].[dbo].[GroupAssociation];
SELECT * FROM [Lab_2].[dbo].[Groups];
SELECT * FROM [Lab_2].[dbo].[PaperProfessorsAssociation];
SELECT * FROM [Lab_2].[dbo].[PaperStudentAssociation];
SELECT * FROM [Lab_2].[dbo].[Professors];
SELECT * FROM [Lab_2].[dbo].[Students];
SELECT * FROM [Lab_2].[dbo].[StudentSubjectGrades];
SELECT * FROM [Lab_2].[dbo].[Subjects];


--�������� ������ ��� ��������������
INSERT INTO [Lab_2].[dbo].[Groups] (GroupName, StudyType)
VALUES
    ('KS-22', 'full-time'),
    ('KI-22', 'part-time'),
    ('KM-22', 'full-time'),
    ('KE-22', 'part-time'),
    ('KS-23-1', 'full-time'),
    ('KI-23-1', 'part-time'),
    ('KM-23-1', 'full-time'),
    ('KE-23-1', 'part-time'),
    ('KS-23-2', 'full-time'),
    ('KI-23-2', 'part-time'),
    ('KM-23-2', 'full-time'),
    ('KE-23-2', 'part-time');
  
--������� ����
DECLARE @StudentStartPosition INT = 3;
DECLARE @StudentID INT = @StudentStartPosition;
DECLARE @InsertedStudents INT = 25;
DECLARE @GroupID INT = 1;
DECLARE @GroupMAX INT = 12;
DECLARE @PaymentType NVARCHAR(10);

WHILE @StudentID <= @InsertedStudents + @StudentID  -- ��� ��� �������� ����������� �������� ID ��������
BEGIN
    -- �������� ���������� ����� PaymentType ��� ������� ��������
    SET @PaymentType = CASE WHEN RAND() > 0.5 THEN 1 ELSE 0 END;

    -- ���������� ����� � ������� GroupsAssociation
    INSERT INTO [Lab_2].[dbo].[GroupAssociation] (StudentID, GroupID, PaymentType)
    VALUES (@StudentID, @GroupID, @PaymentType);

    -- �������� �������� StudentID �� GroupID
    SET @StudentID = @StudentID + 1;
    SET @GroupID = @GroupID + 1;

    -- ��������, �� �� ��������� ������������� �������� ID ��������
	IF @StudentID >= @InsertedStudents + @StudentStartPosition
		BREAK;

    IF @GroupID > @GroupMAX  
        SET @GroupID = 1;
END;

--������ ������� (�1)
ALTER TABLE [Lab_2].[dbo].[Groups]
ADD CONSTRAINT chk_form_of_study CHECK (StudyType IN ('full-time', 'part-time'));

--������ 5 �������� � ���������
INSERT INTO [Lab_2].[dbo].[Students] (SurName, Name, LastName, Sex, Date, Adress, Number, Consript)
VALUES
  ('�����', '���������', '��������', '�', '2003-05-15', '�����, ���. ��������, 38', '+380501234567', '���������'),
  ('�������', '����', '���㳿���', '�', '2000-02-20', '�����, ���. ��������, 38', '+380502345678', '���������'),
  ('��������', '����', '³��������', '�', '2001-03-15', '�����, ���. ��������, 38', '+380987654321',  '���������'),
  ('�������', '����', '�������', '�', '2004-07-22', '�����, ���. ��������, 38', '+380955556666', '�����������'),
  /*5*/('�����', '������', '��������', '�', '2005-11-10', '�����, ���. ��������, 38', '+380933334444',  '���������');

--2 ������� �� ����� �.�.�. (������� - �������, ��'� �� �� ������� - ���������) ��� ��������, �� ������ � ����������.
SELECT CONCAT(Surname, ' ', LEFT(Name, 1), '.', LEFT(LastName, 1), '.') AS '�.�.�.'
FROM [Lab_2].[dbo].[Students]
WHERE Adress LIKE '%�����, ���. ��������%';

--3 ������� �� ����� �.�.�. (������� - �������, ��'� �� �� ������� - ���������) ��� �������������'������ �������� (�������, 18<= �� < 25, ������� �� �������� ������).
SELECT CONCAT(Surname, ' ', LEFT(Name, 1), '.', LEFT(LastName, 1), '.') AS '�.�.�.',
	   DATEDIFF(YEAR, Date, GETDATE()) AS '³�'
FROM [Lab_2].[dbo].[Students]
WHERE Sex = '�'
AND  DATEDIFF(YEAR, Date, GETDATE()) BETWEEN 18 AND 24
AND Consript = '���������'

-- 4 ������� �� ����� �.�.�. (������� - �������, ��'� �� �� ������� - ���������) � � ����� ��� ��������, ��
SELECT
    CONCAT(S.Surname, ' ', S.Name, ' ', LEFT(S.LastName, 1)) AS '�.�.�.',
    SUBSTRING(G.GroupName, CHARINDEX('-', G.GroupName) + 1, 2) AS '� �����'
FROM [Lab_2].[dbo].[Students] AS S
JOIN [Lab_2].[dbo].GroupAssociation AS GA ON S.id = GA.StudentID
JOIN [Lab_2].[dbo].[Groups] AS G ON GA.GroupID = G.id
WHERE G.GroupName LIKE 'KS%'

-- 5 ������� �� ����� �.�.�. (������� - �������, ��'� �� �� ������� - ���������) 
--				� ����� ��� ��������, �� ����� �������� ����� (����� �� ����), � ����� ����� ��� ���������� ����� � �� ��� (������ ��� ����).
-- ������� �� ����� �.�.�. ���������� ��� ��� ��������, ��������� �� �������� ���������� �����
SELECT
    CONCAT(S.SurName, ' ', S.Name, ' ', LEFT(S.LastName, 1)) AS '�.�.�.',
    G.GroupName AS '�����',
    CASE
        WHEN PSA.PaperID IS NOT NULL THEN '����'
        WHEN ASA.ArticleID IS NOT NULL THEN '������'
        ELSE '���� ���������� �����'
    END AS '��� �����',
    COALESCE(AA.Title, CP.Title) AS '����� ��������� �����'
FROM [Lab_2].[dbo].Students AS S
JOIN [Lab_2].[dbo].GroupAssociation AS GA ON S.id = GA.StudentID
JOIN [Lab_2].[dbo].Groups AS G ON GA.GroupID = G.id
LEFT JOIN [Lab_2].[dbo].ArticleStudentAssociation AS ASA ON S.id = ASA.StudentID
LEFT JOIN [Lab_2].[dbo].Articles AS AA ON ASA.ArticleID = AA.id
LEFT JOIN [Lab_2].[dbo].PaperStudentAssociation AS PSA ON S.id = PSA.StudentID
LEFT JOIN [Lab_2].[dbo].ConferencePapers AS CP ON PSA.PaperID = CP.id;

-- ������� �� ����� �.�.�. ���������� ��� �������� � ����������� �������
SELECT
    CONCAT(S.SurName, ' ', S.Name, ' ', LEFT(S.LastName, 1)) AS '�.�.�.',
    G.GroupName AS '�����',
    CASE
        WHEN PSA.PaperID IS NOT NULL THEN '����'
        WHEN ASA.ArticleID IS NOT NULL THEN '������'
        ELSE '���� ���������� �����'
    END AS '��� �����',
    COALESCE(AA.Title, CP.Title) AS '����� ��������� �����'
FROM [Lab_2].[dbo].Students AS S
JOIN [Lab_2].[dbo].GroupAssociation AS GA ON S.id = GA.StudentID
JOIN [Lab_2].[dbo].Groups AS G ON GA.GroupID = G.id
LEFT JOIN [Lab_2].[dbo].ArticleStudentAssociation AS ASA ON S.id = ASA.StudentID
LEFT JOIN [Lab_2].[dbo].Articles AS AA ON ASA.ArticleID = AA.id
LEFT JOIN [Lab_2].[dbo].PaperStudentAssociation AS PSA ON S.id = PSA.StudentID
LEFT JOIN [Lab_2].[dbo].ConferencePapers AS CP ON PSA.PaperID = CP.id
WHERE ASA.ArticleID IS NOT NULL OR PSA.PaperID IS NOT NULL;


--6 ������� ������ �������� � ������ �� ��� ��� ����������� �������� (������� ���������� �� ������ �������).
SELECT
    S.SurName + ' ' + LEFT(S.Name, 1) + '. ' + LEFT(S.LastName, 1) + '.' AS '�.�.�.',
    Su.Name AS '�������',
    SSG.Grade AS '������'
FROM [Lab_2].[dbo].Students AS S
JOIN [Lab_2].[dbo].StudentSubjectGrades AS SSG ON S.id = SSG.StudentID
JOIN [Lab_2].[dbo].Subjects AS Su ON SSG.SubjectID = Su.id
WHERE S.id = 3;--��� id �������

--7 �������������� common table expressions �������� ������� ���: ����� ��������, ��� ������������, ����� �����.
WITH StudentInfo AS (
    SELECT
        S.id AS StudentID,
        G.GroupName,
        (YEAR(GETDATE()) - CAST(SUBSTRING(G.GroupName, 4, 2) AS INT) + 1) - 2000 AS CourseNumber 
    FROM [Lab_2].[dbo].Students AS S
    JOIN [Lab_2].[dbo].GroupAssociation AS GA ON S.id = GA.StudentID
    JOIN [Lab_2].[dbo].Groups AS G ON GA.GroupID = G.id
)

SELECT DISTINCT
    Su.Name AS SubjectName,
    SUBSTRING(GA.GroupName, 1, CHARINDEX('-', GA.GroupName) - 1) AS SpecialtyCode,
    SI.CourseNumber
FROM StudentInfo AS SI
JOIN [Lab_2].[dbo].StudentSubjectGrades AS SSG ON SI.StudentID = SSG.StudentID
JOIN [Lab_2].[dbo].Subjects AS Su ON SSG.SubjectID = Su.id
JOIN [Lab_2].[dbo].Groups AS GA ON SI.GroupName = GA.GroupName;


