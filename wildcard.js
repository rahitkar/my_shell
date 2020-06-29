const fs = require('fs');

const getMatchedStrings = function(commands, txt) {
  const matcher = new RegExp(txt, 'g');
  return commands.filter((command) => {
    return command.match(matcher);
  });
};

const getMatchingCommands = function(commands, txt) {
  const options = txt.split('*');
  if (options[0] === '') {
    return getMatchedStrings(commands, options[1] + '$');
  }
  if (options[1] === '') {
    return getMatchedStrings(commands, '^' + options[0]);
  }
  const new_commands = getMatchedStrings(commands, '^' + options[0]);
  return getMatchedStrings(new_commands, options[1] + '$');
};

const expand_asterisk = function(string) {
  const txt = process.argv[2];
  commands = string.split('\n');
  
  commands = commands.filter(a => a);
  
  const matchedCommands = getMatchingCommands(commands, txt);
  matchedCommands.push("\0");
  
  fs.writeFileSync('out', matchedCommands.join('\n'), "UTF8");
};

expand_asterisk(fs.readFileSync('out', 'UTF8'));
