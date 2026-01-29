import { readFile, writeFile } from 'fs/promises';

const inputFiles = ['file1.txt', 'file2.txt', 'file3.txt'];
const outputFileName = 'merged_output.txt';
const encoding = 'utf-8';

async function mergeAndWriteFiles() {
    console.log(`Початок паралельного читання ${inputFiles.length} файлів...`);

    try {

        const fileContents = await Promise.all(
            inputFiles.map(file => readFile(file, { encoding }))
        );

        console.log('Всі файли успішно прочитано.');


        const mergedContent = fileContents.join(' ');
        
        console.log(`Об’єднаний вміст: "${mergedContent}"`);

        await writeFile(outputFileName, mergedContent);

        console.log(`Результат успішно записано у файл: ${outputFileName}`);

    } catch (error) {
        console.error('Виникла помилка під час операції з файлами:', error.message);
    }
}

mergeAndWriteFiles();