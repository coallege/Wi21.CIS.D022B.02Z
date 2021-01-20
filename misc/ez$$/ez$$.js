void async function ez$$() {
	const auth_token = JSON.parse(
		localStorage["ember_simple_auth-session-5"]
	).authenticated.session.auth_token;

	const path = location.pathname;

	const APIv1 = "https://zyserver.zybooks.com/v1";

	const req_url = `${APIv1}${path}?auth_token=${auth_token}`;

	const res = await fetch(req_url).then(data => data.json());

	window.res = res;

	console.clear();
	console.log("ez$$");

	const resources = res?.section?.content_resources;

	if (!Array.isArray(resources)) {
		console.log("FATAL: RESPONSE NOT ARRAY");
		console.log(res);
		return;
	}

	const isParticipation = ({activity_type}) =>
		activity_type === "participation";
	const participation = resources.filter(isParticipation);

	participation:
	for (const part of participation) {
		const content_resource_id = part.id;
		const qs = `div[content_resource_id="${content_resource_id}"]`;

		console.group(qs);
		const ele = document.querySelector(qs);
		try {
			if (!ele) {
				console.warn("BAD ELEMENT");
				continue participation;
			}
			console.info("OK ELEMENT");

			const payload = ele.children[1];
			const shortAnswerPayload = payload?.children[1];
			if (!shortAnswerPayload) {
				console.error("BAD SHORT ANSWER PAYLOAD");
				continue participation;
			}
			console.info("OK SHORT ANSWER PAYLOAD");

			/** @type {HTMLDivElement[]} */
			const questions =
				[...shortAnswerPayload.children]
					.map(qsa => qsa.firstChild);
			const len = questions.length;

			console.groupCollapsed("QUESTIONS");
			questions:
			for (let i = 0; i < len; ++i) {
				const container = questions[i].children?.[0];
				if (!container) {
					console.warn(`BAD CONTAINER ${i}`);
					continue questions;
				}
				console.info(`OK CONTAINER ${i}`);

				const questionData = part.payload.questions[i];
				const answerBox    = document.createElement("span");
				answerBox.style.fontWeight = "bold";
				answerBox.style.fontFamily = "Consolas, monospace";

				if (questionData.answers) {
					console.info(`OK SHORT ANSWER ${i}`);
					answerBox.innerText += questionData
						.answers
						.join(", ");
				} else if (questionData.choices) {
					console.info(`OK MULTI CHOICE ${i}`);
					const humanIndex = questionData
						.choices
						.findIndex(({ correct }) => correct)
						+ 1
						;

					answerBox.innerText += `#${humanIndex}`;
				} else {
					console.warn(`BAD QUESTION ${i}`);
				}

				container.appendChild(answerBox);
			}
			console.groupEnd();
		} finally {
			console.groupEnd();
		}
	}
}();
void function ez$$_anim() {
	const eight_speeds = [
		...document.querySelectorAll("input[aria-label='2x speed']")
	];

	for (const checkbox of eight_speeds) {
		if (checkbox.value === "false") {
			checkbox.click();
		}
	}

	const start_buttons = [
		...document.querySelectorAll("button.start-button.start-graphic")
	];

	for (const start_button of start_buttons) {
		start_button.click();
	}

	for (let i = 0; i < 30; ++i) {
		setTimeout(() => {
			/** @type {HTMLButtonElement[]} */
			const play_buttons = [
				...document.querySelectorAll("div.play-button.bounce")
			];

			for (const play_button of play_buttons) {
				play_button.click();
			}
		}, 2000 * i);
	}
}();
