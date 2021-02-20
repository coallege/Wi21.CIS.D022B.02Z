const fs = require("fs");
const path = require("path");

const self = "revision";

if (fs.existsSync(self)) {
	if (fs.statSync(self).isDirectory()) {
		fs.rmSync(self, {recursive: true, force: true});
	} else {
		throw new Error(`non-directory at ${self}`);
	}
}
fs.mkdirSync(self);

const dat = `${self}.dat`;
if (fs.existsSync(dat)) {
	var rev = fs.readFileSync(dat, "utf8") | 0;
} else {
	var rev = -1;
}

rev++;

for (const dirent of fs.readdirSync(".", {withFileTypes: true})) {
	if (!dirent.isFile()) {
		continue;
	}

	if (!dirent.name.endsWith(".cxx")) {
		continue;
	}

	const basename = path.parse(dirent.name).name;

	fs.copyFileSync(
		dirent.name,
		`${self}/gannon_cole_${basename}_r${rev}.cpp`,
	);
}

fs.writeFileSync(dat, rev.toString());