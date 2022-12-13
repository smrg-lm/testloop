Feedback : UGen {
	*ar { |input, maxDelay = 0.3, delayTime = 0.3, k = 0.9|
		^this.multiNew('audio', input, maxDelay, delayTime, k);
	}

	// checkInputs {
	// 	/* TODO */
	// 	^this.checkValidInputs;
	// }
}
