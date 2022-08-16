package flat

type Voice struct {
	name       string
	features   map[string]any
	ffunctions map[string]any
	init       *utterance
}

type Wave struct {
	Type        *int8
	SampleRate  int32
	NumSamples  int32
	NumChannels int32
	Padding     [4]byte
	Samples     *int16
}

type utterance struct {
	features   map[string]any
	ffunctions map[string]any
	relations  map[string]any
}


func NewKal() *Voice {
	return newVoice("kal")
}
func newVoice(name string) *Voice {
	switch name {
	case "kal": return instantiateKal()
	}
	return nil
}
func instantiateKal() *Voice {
	v := &Voice{
		name: "kal",
		features: make(map[string]any),
		ffunctions: make(map[string]any),
	}
	// basic values for synthesizing with this voice
	v.features["name"] = "cmu_us_kal_diphone"
	// lexicon
	// intonation
	v.features["int_f0_target_mean"] = 95.0
	v.features["int_f0_target_stddev"] = 11.0
	v.features["duration_stretch"] = 1.1


	return v
}
