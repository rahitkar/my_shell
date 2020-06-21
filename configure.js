const fs = require('fs');

const readline = require('readline');
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

const main = function() {
  rl.question('Enter your prompt name: ', function(name) {
    let shell_info;
    shell_info = `char prompt[] ="${name}";\n`;

    rl.question(
      'For prompt colour Enter a number\nred = 0 yellow = 1 blue = 2 green = 3 white = 4 : ',
      (colour_flag) => {
        shell_info += `int prmt_colour_flag = ${colour_flag};\n`;

        rl.question(
          'For path colour Enter a number\nred = 0 yellow = 1 blue = 2 green = 3 white = 4 : ',
          (colour_flag) => {
            shell_info += `int pwd_colour_flag = ${colour_flag};\n`;
            fs.writeFileSync('./config.h', shell_info, 'UTF8');
            rl.close();
          }
        );
      }
    );
  });
};
// 'For prompt colour Enter a number\nred = 0\nyellow = 1\nblue = 2\ngreen = 3\nwhite = 4 : '
main();
