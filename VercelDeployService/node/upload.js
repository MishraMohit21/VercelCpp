const { S3 } = require("aws-sdk");
const fs = require("fs");
const path = require("path");

const { accessKeyId, secretAccessKey, endpoint } = require("./sec/keys");

const s3 = new S3({
    accessKeyId: accessKeyId,
    secretAccessKey: secretAccessKey,
    endpoint: endpoint,
});

async function uploadFile(fileName, localPath) {
    try {
        const fileContent = fs.readFileSync(localPath);
        const response = await s3.upload({
            Body: fileContent,
            Bucket: "vercelclone",
            Key: fileName
        }).promise();

        return response.Location;
    } catch (error) {
        console.error("Error uploading file:", error);
        throw error;
    }
}

function copyFinalDist(id) {
    const folderPath = path.join(__dirname, `Output/${id}/dist`);
    const allFiles = getAllFiles(folderPath);

    allFiles.forEach(file => {
        uploadFile(`dist/${id}/` + file.slice(folderPath.length + 1), file);
    });
}

module.exports = {
    copyFinalDist
};
