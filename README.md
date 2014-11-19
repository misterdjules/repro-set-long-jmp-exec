### How to run the test

```
$ sudo npm install -g node-gyp
$ node-gyp configure
$ node-gyp build
$ node ./index.js
```

If the program outputs:
```
jump returned
stdout: foo

exec returned
```
It means the issue that this repository tries to reproduce is fixed.
