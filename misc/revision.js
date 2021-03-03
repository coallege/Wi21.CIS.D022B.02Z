const fs = require("fs");
const path = require("path");
const {execSync} = require("child_process");

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

	const base_in = path.parse(dirent.name).name;
	const base_out = `${self}/gannon_cole_${base_in}_r${rev}`;
	const cpp = `${base_out}.cpp`;

	fs.copyFileSync(dirent.name, cpp);

	if (process.platform === "win32") {
		const exe = `${base_out}.exe`;
		console.log(`CXX ${cpp}`);
		execSync(`wsl clang++ ${cpp} -Wall -Wextra -o ${exe}`, {stdio: "inherit"});
		console.log(`RM  ${cpp}`);
		fs.unlinkSync(exe);
	}
}

fs.writeFileSync(dat, rev.toString());
