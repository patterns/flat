package flat


func TextToWave(text string, voice *Voice) *Wave {
	ut, err := synthText(text,voice)
	if err != nil {
		return nil
	}
	if w, ok := ut.features["wave"].(*Wave); ok {
		return w
	}
	return nil
}

func synthText(text string, voice *Voice) (*utterance, error) {
	ut := &utterance{
		features: make(map[string]any),
		ffunctions: make(map[string]any),
		relations: make(map[string]any),
	}
	ut.features["input_text"] = text
	//uttInit(ut, voice)

	for _, mo := range synthMethodText {
		ut.applySynthModule(mo)
	}
}
type smod struct {
	hookname string
	defhook uttfunc
}
type uttfunc func(*utterance) *utterance

var synthMethodText = []smod {
    smod{ "tokenizer_func", defaultTokenization },
    /*
    smod{ "textanalysis_func", default_textanalysis },
    smod{ "pos_tagger_func", default_pos_tagger },
    smod{ "phrasing_func", default_phrasing },
    smod{ "lexical_insertion_func", default_lexical_insertion },
    smod{ "pause_insertion_func", default_pause_insertion },
    smod{ "intonation_func", cart_intonation },
    smod{ "duration_model_func", cart_duration },
    */
}

func (u *utterance) applySynthModule(mo smod) {
	if v, ok := u.features[mo.hookname].(uttfunc); ok {
		v(u);
	}
	else if mo.defhook != nil {
		mo.defhook(u)
	}
}

// union/merge the utterance and voice features
func uttInit(u *utterance, vox *Voice) *utterance {

    // Link the vox features into the utterance features so the voice  
    // features will be searched too (after the utt ones)              
    feat_link_into(vox->features,u->features);
    feat_link_into(vox->ffunctions,u->ffunctions);

    // Do the initialization function, if there is one 

    return u
}


defaultTokenization(ut *utterance) *utterance {
    const char *text,*token;
    cst_tokenstream *fd;
    cst_item *t;
    cst_relation *r;

    text = utt_input_text(u);
    r = utt_relation_create(u,"Token");
    fd = ts_open_string(text,
	get_param_string(u->features,"text_whitespace",NULL),
	get_param_string(u->features,"text_singlecharsymbols",NULL),
	get_param_string(u->features,"text_prepunctuation",NULL),
        get_param_string(u->features,"text_postpunctuation",NULL));
    
    while(!ts_eof(fd))
    {
	token = ts_get(fd);
	if (cst_strlen(token) > 0)
	{
	    t = relation_append(r,NULL);
	    item_set_string(t,"name",token);
	    item_set_string(t,"whitespace",fd->whitespace);
	    item_set_string(t,"prepunctuation",fd->prepunctuation);
	    item_set_string(t,"punc",fd->postpunctuation);
	    item_set_int(t,"file_pos",fd->file_pos);
	    item_set_int(t,"line_number",fd->line_number);
	}
    }

    ts_close(fd);
    
    return u;
}
