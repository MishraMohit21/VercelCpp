const { S3 } = require("aws-sdk");
const fs = require("fs");
const path = require("path");

const { accessKeyId, secretAccessKey, endpoint } = require("./sec/keys");

const s3 = new S3({
    accessKeyId: accessKeyId,
    secretAccessKey: secretAccessKey,
    endpoint: endpoint,
});

async function downloadFromS3_R2(prefix) {
    const allFiles = await s3.listObjectsV2({
        Bucket: "vercelbutbetter",
        Prefix: prefix
    }).promise();

    const allPromises = allFiles.Contents?.map(({ Key }) => {
        return new Promise(async (resolve) => {
            if (!Key) {
                resolve("");
                return;
            }
            const finalOutputPath = path.join(__dirname, Key);
            const outputFile = fs.createWriteStream(finalOutputPath);
            const dirName = path.dirname(finalOutputPath);

            if (!fs.existsSync(dirName)) {
                fs.mkdirSync(dirName, { recursive: true });
            }

            s3.getObject({
                Bucket: "vercelbutbetter",
                Key
            }).createReadStream().pipe(outputFile).on("finish", () => {
                resolve("");
            });
        });
    }) || [];

    console.log("Awaiting downloads...");
    await Promise.all(allPromises.filter(x => x !== undefined));
}




module.exports = {
    downloadFromS3_R2
};
