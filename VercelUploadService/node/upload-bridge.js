// upload-bridge.js
const { uploadFile } = require('./aws');

// Get arguments from command line
const fileName = process.argv[2];
const localPath = process.argv[3];

// Perform upload
uploadFile(fileName, localPath)
  .then(url => {
    console.log(url);
    process.exit(0);
  })
  .catch(error => {
    console.error(error);
    process.exit(1);
  });