const { downloadFromS3_R2 } = require("./download");

// Ensure a prefix argument is provided
if (process.argv.length < 3) {
    console.error("Usage: node runDownload.js <prefix>");
    process.exit(1);
}

const prefix = process.argv[2];

(async () => {
    try {
        console.log(`Downloading files from S3 with prefix: ${prefix}`);
        await downloadFromS3_R2(prefix);
        console.log("Download complete!");
    } catch (error) {
        console.error("Error downloading files:", error);
        process.exit(1);
    }
})();
