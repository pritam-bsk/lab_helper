const express = require('express');
const app = express();

const fs = require('node:fs');

let code = '';

fs.readFile('code.cpp', 'utf8', (err, data) => {
    if (err) {
        console.error('Error reading file:', err);
        return;
    }
    code = data;
    console.log(data);
});


app.post('/', (req, res) => {
    res.send(code); 
});

app.listen(3000, () => console.log('Express server running on port 3000'));
