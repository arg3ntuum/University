const http = require("http");

const data = {
  name: "Ростислав",
  age: 21,
  course: "JavaScript",
  skills: ["HTML", "CSS", "JS"]
};

http.createServer((req, res) => {
  res.writeHead(200, {
    "Content-Type": "application/json",
    "Access-Control-Allow-Origin": "*",  
    "Access-Control-Allow-Methods": "GET, POST, OPTIONS",
    "Access-Control-Allow-Headers": "Content-Type"
  });

  res.end(JSON.stringify(data));
}).listen(3000, () => console.log("Сервер працює на http://localhost:3000"));
