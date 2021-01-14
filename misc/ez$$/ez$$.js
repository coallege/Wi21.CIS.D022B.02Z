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
			debugger;
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

			const questions =
				[...shortAnswerPayload.children]
					.map(qsa => qsa.firstChild);
			const len = questions.length;

			console.groupCollapsed("QUESTIONS");
			questions:
			for (let i = 0; i < len; ++i) {
				const question = questions[i];
				const title = question.children[0]?.children?.[1];
				if (!title) {
					console.warn(`BAD TITLE ${i}`);
					continue questions;
				}
				console.info(`OK TITLE ${i}`);

				const questionData = part.payload.questions[i];
				if (questionData.answers) {
					console.info(`OK SHORT ANSWER ${i}`);
					title.innerHTML += ` <i>(${questionData.answers.join(", ")})</i>`;
				} else if (questionData.choices) {
					console.info(`OK MULTI CHOICE ${i}`);
					title.innerHTML += ` <i>(#${
						questionData.choices.findIndex(({ correct }) => correct) + 1
					})</i>`;
				} else {
					console.warn(`BAD QUESTION ${i}`);
				}
			}
			console.groupEnd();
		} finally {
			console.groupEnd();
		}
	}
}();
