//Завдання 1 з 3: Додати та видалити CSS-клас
// Зробіть так, щоб натискання на зображення:
// Видаляло CSS-клас background--active із зовнішнього <div>.
// Додавало клас picture--active до тегу <img>.
// Повторне натискання на фон має відновлювати початкові CSS-класи.
// Візуально ви маєте очікувати, що:
// Натискання на зображення видаляє фіолетовий фон і підсвічує рамку зображення.
// Повторне натискання (за межами зображення, але в межах div) підсвічує фон, але видаляє підсвічування рамки зображення.
///////////////////////////////////////////////////////////////////////
import { useState } from 'react';

export default function Picture() {
  const [isActive, setIsActive] = useState(false);
  const divClassName = 'background' + (isActive ? '' : ' background--active');
  
  const imgClassName = 'picture' + (isActive ? ' picture--active' : '');

  const handleClick = () => {
    setIsActive(!isActive);
  };

  return (
    <div 
      className={divClassName}
      onClick={handleClick} // Це обробляє кліки в межах div
    >
      <img
        className={imgClassName}
        alt="Райдужні будинки в Кампунг Пелангі, Індонезія"
        src="https://i.imgur.com/5qwVYb1.jpeg"
      />
    </div>
  );
}