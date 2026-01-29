const express = require('express');
const bodyParser = require('body-parser'); 
const cors = require('cors'); 
const app = express();
const PORT = 3000;

// Імітація бази даних
let tasks = [
    { id: 1, title: 'Завершити завдання', completed: false },
    { id: 2, title: 'Налаштувати сервер', completed: true }
];
let nextId = 3;

// Middleware
app.use(cors()); 
app.use(bodyParser.json()); 
app.use(bodyParser.urlencoded({ extended: true })); 

// ======================================================
// POST /tasks: Створити нове завдання
// ======================================================
app.post('/tasks', (req, res) => {
    console.log(`[${new Date().toLocaleTimeString()}] POST /tasks`);
    const newTask = req.body;
    
    if (!newTask || !newTask.title) {
        return res.status(400).json({ error: 'Поле "title" є обов\'язковим.' });
    }

    const task = {
        id: nextId++,
        title: newTask.title,
        completed: false
    };

    tasks.push(task);
    res.status(201).json(task);
});

// ======================================================
// GET /tasks: Отримати всі завдання
// ======================================================
app.get('/tasks', (req, res) => {
    console.log(`[${new Date().toLocaleTimeString()}] GET /tasks`);
    res.status(200).json(tasks);
});

// ======================================================
// Обробка неіснуючих ресурсів 
// ======================================================
app.use((req, res) => {
    res.status(404).json({ error: "Ресурс не знайдено на цьому сервері." });
});

// Запуск сервера
app.listen(PORT, () => {
    console.log(`REST API Server запущено на http://localhost:${PORT}`);
});
