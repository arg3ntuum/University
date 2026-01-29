// client.js

// ======================================================
// (а) WebSocket: ЧАТ
// ======================================================

const ws = new WebSocket('ws://localhost:3000');
const chatWindow = document.getElementById('chat-window');
const chatInput = document.getElementById('chat-input');
const USER_ID = Math.floor(Math.random() * 1000); // Генеруємо унікальний ID

ws.onopen = () => {
    console.log('WebSocket підключено.');
    appendMessage({ type: 'status', message: `Ви підключилися як Користувач-${USER_ID}` });
};

ws.onmessage = event => {
    try {
        const data = JSON.parse(event.data);
        if (data.type === 'chat' || data.type === 'status') {
            appendMessage(data);
        }
    } catch (e) {
        console.error('Помилка парсингу повідомлення:', e);
    }
};

ws.onerror = error => {
    console.error('WebSocket помилка:', error);
    appendMessage({ type: 'status', message: 'Помилка підключення до чату.' });
};

function appendMessage(data) {
    const messageDiv = document.createElement('div');
    messageDiv.classList.add('message');

    if (data.type === 'status') {
        messageDiv.classList.add('status');
        messageDiv.textContent = `[СИСТЕМА] ${data.message}`;
    } else if (data.type === 'chat') {
        // Припускаємо, що повідомлення надходить у форматі "Користувач-123: Привіт"
        messageDiv.textContent = `[${data.timestamp}] ${data.message}`;
    }

    chatWindow.appendChild(messageDiv);
    // Прокручування до останнього повідомлення
    chatWindow.scrollTop = chatWindow.scrollHeight;
}

function sendMessage() {
    const message = chatInput.value.trim();
    if (message) {
        const fullMessage = `Користувач-${USER_ID}: ${message}`;
        ws.send(fullMessage);
        chatInput.value = ''; // Очищення поля вводу
    }
}

// Надсилання повідомлення по Enter
chatInput.addEventListener('keypress', event => {
    if (event.key === 'Enter') {
        sendMessage();
    }
});

// ======================================================
// (в) Web Worker (Факторіал)
// ======================================================

function calculateFactorial() {
    const input = document.getElementById('worker-input');
    const number = parseInt(input.value, 10);
    const resultElement = document.getElementById('worker-result');
    const statusElement = document.getElementById('worker-status');

    if (isNaN(number) || number < 1) {
        alert('Будь ласка, введіть дійсне число (>= 1).');
        return;
    }

    // Зміна UI перед запуском Worker
    statusElement.textContent = 'Обчислення...';
    resultElement.textContent = 'Триває... (Інтерфейс не заблоковано)';

    // Створення нового Web Worker
    const worker = new Worker('worker.js');

    // Надсилання даних Worker'у
    worker.postMessage(number);

    // Обробка повідомлень від Worker'а
    worker.onmessage = function (e) {
        if (e.data.status === 'calculating') {
            statusElement.textContent = 'Обчислення розпочато у фоновому потоці...';
        } else if (e.data.status === 'done') {
            const resultString = e.data.result;
            const truncatedResult = resultString.substring(0, 100) + (resultString.length > 100 ? '...' : '');

            statusElement.textContent = `Завершено! (${e.data.number}!)`;
            resultElement.textContent = truncatedResult;

            // Завершення роботи Worker'а
            worker.terminate();
        }
    };

    worker.onerror = error => {
        statusElement.textContent = 'Помилка Worker!';
        console.error('Web Worker помилка:', error);
    };
}