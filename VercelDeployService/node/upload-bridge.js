const { copyFinalDist } = require("./upload");

// Ensure an ID argument is provided
if (process.argv.length < 3) {
    console.error("Usage: node runUpload.js <id>");
    process.exit(1);
}

const id = process.argv[2];

(async () => {
    try {
        console.log(`Uploading files for ID: ${id}`);
        await copyFinalDist(id);
        console.log("Upload complete!");
    } catch (error) {
        console.error("Error uploading files:", error);
        process.exit(1);
    }
})();
