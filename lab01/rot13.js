function rot13_c(c) {
	const c_c = c.charCodeAt(0);
	const A_c = 'A'.charCodeAt(0);
	const z_c = 'z'.charCodeAt(0);
	const Z_c = 'Z'.charCodeAt(0);
	const a_c = 'a'.charCodeAt(0);
	debugger;
	if (c_c < A_c || c_c > z_c) {
		console.log("oob");
		return c;
	}

	// uppercase branch
	if (c_c <= Z_c) {
		console.log("ucase");
		return String.fromCharCode(((c_c + 13 - A_c) % 26) + A_c);
	}

	// lowercase branch
	if (c_c >= a_c) {
		console.log("lcase");
		return String.fromCharCode(((c_c + 13 - a_c) % 26) + a_c);
	}
}
