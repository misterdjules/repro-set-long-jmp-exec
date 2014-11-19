var jump = require('./build/Release/jump').jump;
var exec = require('child_process').exec;

jump(function(err, data) {
  console.warn('jump returned');

  exec('echo foo', function(err, stdout, stderr) {
    console.log('stdout:', stdout);
    console.warn('exec returned');
  });
});
