// s3manager.ts
// s3manager.js
const { S3 } = require('aws-sdk');
const fs = require('fs');
const { accessKeyId, secretAccessKey, endpoint } = require('./sec/keys');

const s3 = new S3({
  accessKeyId: accessKeyId,
  secretAccessKey: secretAccessKey,
  endpoint: endpoint
});

const uploadFile = async (fileName, localPath) => {
  try {
    const fileContent = fs.readFileSync(localPath);
    const response = await s3.upload({
      Body: fileContent,
      Bucket: "vercelbutbetter",
      Key: fileName,
    }).promise();
    return response.Location;
  } catch (error) {
    console.error("Error uploading file:", error);
    throw error;
  }
};

// For CommonJS exports
module.exports = { uploadFile };