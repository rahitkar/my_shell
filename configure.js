const fs = require('fs');

const readline = require('readline');
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

const main = function() {
  rl.question('Enter your prompt name: ', function(name) {
    let promptName = 'char prompt[] =';
    fs.writeFileSync('./config.h', promptName.concat(`"${name}";`), 'UTF8');
    rl.close();
  });
};

main();
