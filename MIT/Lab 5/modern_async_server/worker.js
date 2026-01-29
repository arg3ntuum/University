// worker.js

// Функція для обчислення факторіала великого числа
// Використовуємо BigInt для підтримки великих чисел, що необхідно для факторіалів > 20
function factorial(n) {
    const num = BigInt(n);
    if (num < 0n) return 0n;
    if (num === 0n) return 1n;

    let result = 1n;
    for (let i = 2n; i <= num; i++) {
        result *= i;
    }
    return result;
}


// Обробник повідомлень, надісланих з головного потоку
self.onmessage = function(e) {
    const number = e.data; // Отримуємо число для обчислення
    
    // Надсилаємо повідомлення про початок роботи
    self.postMessage({ status: 'calculating' });
    
    // Блокуюче обчислення
    const result = factorial(number);
    
    // Надсилаємо готовий результат назад у головний потік
    self.postMessage({ 
        status: 'done', 
        result: result.toString(),
        number: number 
    });
};