#include "MyTest.h"

namespace MyTest {

/*******************************************************************************************************************
Cycling '74 License for Max-Generated Code for Export
Copyright (c) 2016 Cycling '74
The code that Max generates automatically and that end users are capable of exporting and using, and any
  associated documentation files (the “Software”) is a work of authorship for which Cycling '74 is the author
  and owner for copyright purposes.  A license is hereby granted, free of charge, to any person obtaining a
  copy of the Software (“Licensee”) to use, copy, modify, merge, publish, and distribute copies of the Software,
  and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The Software is licensed to Licensee only for non-commercial use. Users who wish to make commercial use of the
  Software must contact the copyright owner to determine if a license for commercial use is available, and the
  terms and conditions for same, which may include fees or royalties. For commercial use, please send inquiries
  to licensing (at) cycling74.com.  The determination of whether a use is commercial use or non-commercial use is based
  upon the use, not the user. The Software may be used by individuals, institutions, governments, corporations, or
  other business whether for-profit or non-profit so long as the use itself is not a commercialization of the
  materials or a use that generates or is intended to generate income, revenue, sales or profit.
The above copyright notice and this license shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*******************************************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Data m_nob_9;
	Data m_nib_13;
	Delta __m_delta_17;
	Delta __m_delta_33;
	Delta __m_delta_38;
	Delta __m_delta_14;
	Phasor __m_phasor_37;
	Phasor __m_phasor_32;
	PlusEquals __m_pluseq_18;
	PlusEquals __m_pluseq_34;
	PlusEquals __m_pluseq_39;
	PlusEquals __m_pluseq_15;
	SineCycle __m_cycle_25;
	SineCycle __m_cycle_27;
	SineCycle __m_cycle_26;
	SineCycle __m_cycle_24;
	SineCycle __m_cycle_28;
	SineCycle __m_cycle_30;
	SineData __sinedata;
	int vectorsize;
	int __exception;
	t_sample m_history_3;
	t_sample m_history_2;
	t_sample samples_to_seconds;
	t_sample m_history_1;
	t_sample m_sw_11;
	t_sample samplerate;
	t_sample __m_slide_20;
	t_sample m_knob_12;
	t_sample m_history_6;
	t_sample m_history_4;
	t_sample m_history_7;
	t_sample m_history_8;
	t_sample m_history_5;
	t_sample m_knob_10;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_history_2 = ((int)0);
		m_history_3 = ((int)0);
		m_history_4 = ((int)0);
		m_history_5 = ((int)0);
		m_history_6 = ((int)0);
		m_history_7 = ((int)0);
		m_history_8 = ((int)0);
		m_nob_9.reset("nob", ((int)9600), ((int)1));
		m_knob_10 = 1;
		m_sw_11 = 1;
		m_knob_12 = 1;
		m_nib_13.reset("nib", ((int)9600), ((int)1));
		__m_delta_14.reset(0);
		__m_pluseq_15.reset(0);
		__m_delta_17.reset(0);
		__m_pluseq_18.reset(0);
		__m_slide_20 = 0;
		__m_cycle_24.reset(samplerate, 0);
		__m_cycle_25.reset(samplerate, 0);
		__m_cycle_26.reset(samplerate, 0);
		__m_cycle_27.reset(samplerate, 0);
		__m_cycle_28.reset(samplerate, 0);
		__m_cycle_30.reset(samplerate, 0);
		samples_to_seconds = (1 / samplerate);
		__m_phasor_32.reset(0);
		__m_delta_33.reset(0);
		__m_pluseq_34.reset(0);
		__m_phasor_37.reset(0);
		__m_delta_38.reset(0);
		__m_pluseq_39.reset(0);
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		t_sample * __out3 = __outs[2];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		int nob_dim = m_nob_9.dim;
		int nob_channels = m_nob_9.channels;
		int nib_dim = m_nib_13.dim;
		int nib_channels = m_nib_13.channels;
		t_sample iup_21 = (1 / maximum(1, abs(((int)117))));
		t_sample idown_22 = (1 / maximum(1, abs(((int)117))));
		t_sample mul_15 = (m_sw_11 * ((t_sample)0.3));
		int min_23 = (-1);
		int min_29 = (-1);
		int min_31 = (-1);
		samples_to_seconds = (1 / samplerate);
		int min_36 = (-1);
		int min_41 = (-1);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample out3 = ((int)0);
			t_sample mix_3058 = (m_history_8 + (((t_sample)0.0014247580910283) * (m_knob_10 - m_history_8)));
			t_sample mix_130 = mix_3058;
			t_sample mix_3059 = (m_history_7 + (((t_sample)0.0014247580910283) * (mix_130 - m_history_7)));
			t_sample mix_128 = mix_3059;
			t_sample gen_135 = mix_128;
			t_sample history_131_next_133 = fixdenorm(mix_130);
			t_sample history_129_next_134 = fixdenorm(mix_128);
			int gte_140 = (gen_135 >= m_history_4);
			t_sample switch_141 = (gte_140 ? gen_135 : m_history_4);
			t_sample mix_3060 = (m_history_6 + (((t_sample)0.0014247580910283) * (m_knob_12 - m_history_6)));
			t_sample mix_3006 = mix_3060;
			t_sample mix_3061 = (m_history_5 + (((t_sample)0.0014247580910283) * (mix_3006 - m_history_5)));
			t_sample mix_3003 = mix_3061;
			t_sample gen_1892 = mix_3003;
			t_sample history_131_next_3005 = fixdenorm(mix_3006);
			t_sample history_129_next_3002 = fixdenorm(mix_3003);
			int gte_1897 = (gen_1892 >= m_history_3);
			t_sample switch_1898 = (gte_1897 ? gen_1892 : m_history_3);
			int lte_1900 = (gen_1892 <= m_history_2);
			t_sample switch_1901 = (lte_1900 ? gen_1892 : m_history_2);
			int lte_143 = (gen_135 <= m_history_1);
			t_sample switch_144 = (lte_143 ? gen_135 : m_history_1);
			t_sample pass_28 = in1;
			t_sample pass_96 = in1;
			t_sample irange_3063 = (switch_141 - switch_144);
			t_sample sub_3065 = (gen_135 - switch_144);
			t_sample scale_3062 = ((safepow(safediv(sub_3065, irange_3063), ((int)1)) * ((int)2)) + ((int)-1));
			int lt_7 = (scale_3062 < ((int)4));
			int delta_109 = __m_delta_14(lt_7);
			int eq_108 = (delta_109 == ((int)1));
			int plusequals_101 = __m_pluseq_15.post(((int)1), eq_108, 0);
			bool index_ignore_16 = ((plusequals_101 >= nob_dim) || (plusequals_101 < 0));
			if ((!index_ignore_16)) {
				m_nob_9.write(pass_96, plusequals_101, 0);
				
			};
			int gt_23 = (scale_3062 > ((int)64));
			int gt_8 = (scale_3062 > ((int)123));
			int delta_41 = __m_delta_17(gt_8);
			int eq_40 = (delta_41 == ((int)1));
			int plusequals_33 = __m_pluseq_18.post(((int)1), eq_40, 0);
			bool index_ignore_19 = ((plusequals_33 >= nib_dim) || (plusequals_33 < 0));
			if ((!index_ignore_19)) {
				m_nib_13.write(pass_28, plusequals_33, 0);
				
			};
			int or_6 = (lt_7 || gt_8);
			__m_slide_20 = fixdenorm((__m_slide_20 + (((or_6 > __m_slide_20) ? iup_21 : idown_22) * (or_6 - __m_slide_20))));
			t_sample slide_24 = __m_slide_20;
			t_sample noise_17 = noise();
			t_sample mul_16 = (noise_17 * mul_15);
			t_sample add_14 = (mul_16 + ((int)0));
			t_sample add_11 = (add_14 + ((int)0));
			t_sample clamp_12 = ((add_11 <= min_23) ? min_23 : ((add_11 >= ((int)1)) ? ((int)1) : add_11));
			int gt_84 = (scale_3062 > ((int)123));
			int lt_78 = (scale_3062 < ((int)4));
			__m_cycle_24.freq(((int)140));
			t_sample cycle_82 = __m_cycle_24(__sinedata);
			t_sample cycleindex_83 = __m_cycle_24.phase();
			t_sample mul_80 = (cycle_82 * gt_84);
			t_sample mul_79 = (mul_80 * ((t_sample)0.2));
			__m_cycle_25.freq(((int)50));
			t_sample cycle_2157 = __m_cycle_25(__sinedata);
			t_sample cycleindex_2158 = __m_cycle_25.phase();
			__m_cycle_26.freq(((int)120));
			t_sample cycle_76 = __m_cycle_26(__sinedata);
			t_sample cycleindex_77 = __m_cycle_26.phase();
			t_sample mul_74 = (cycle_76 * lt_78);
			t_sample mul_73 = (mul_74 * ((t_sample)0.2));
			__m_cycle_27.freq(((int)100));
			t_sample cycle_2151 = __m_cycle_27(__sinedata);
			t_sample cycleindex_2152 = __m_cycle_27.phase();
			t_sample mul_1410 = (scale_3062 * ((int)20));
			t_sample add_1409 = (mul_1410 + ((int)80));
			t_sample mtof_1759 = mtof(add_1409, ((int)440));
			__m_cycle_28.freq(mtof_1759);
			t_sample cycle_92 = __m_cycle_28(__sinedata);
			t_sample cycleindex_93 = __m_cycle_28.phase();
			t_sample mul_90 = (cycle_92 * ((t_sample)0.4));
			t_sample add_86 = (mul_90 + mul_73);
			t_sample add_72 = (add_86 + mul_79);
			t_sample clamp_71 = ((add_72 <= min_29) ? min_29 : ((add_72 >= ((int)1)) ? ((int)1) : add_72));
			t_sample irange_3067 = (switch_1898 - switch_1901);
			t_sample sub_3069 = (gen_1892 - switch_1901);
			t_sample scale_3066 = ((safepow(safediv(sub_3069, irange_3067), ((int)1)) * ((int)2)) + ((int)-1));
			int gt_2159 = (scale_3066 > ((int)123));
			t_sample mul_2155 = (cycle_2157 * gt_2159);
			t_sample mul_2154 = (mul_2155 * ((t_sample)0.2));
			int lt_2153 = (scale_3066 < ((int)4));
			t_sample mul_2149 = (cycle_2151 * lt_2153);
			t_sample mul_2148 = (mul_2149 * ((t_sample)0.2));
			t_sample mul_2145 = (scale_3066 * ((int)20));
			t_sample add_2144 = (mul_2145 + ((int)80));
			t_sample mtof_2162 = mtof(add_2144, ((int)440));
			__m_cycle_30.freq(mtof_2162);
			t_sample cycle_2164 = __m_cycle_30(__sinedata);
			t_sample cycleindex_2165 = __m_cycle_30.phase();
			t_sample mul_2447 = (cycle_2164 * ((t_sample)0.3));
			t_sample add_2160 = (mul_2447 + mul_2148);
			t_sample add_2147 = (add_2160 + mul_2154);
			t_sample clamp_2146 = ((add_2147 <= min_31) ? min_31 : ((add_2147 >= ((int)1)) ? ((int)1) : add_2147));
			t_sample add_2341 = (clamp_71 + clamp_2146);
			t_sample add_2483 = (add_2341 + clamp_12);
			if ((eq_108 != 0)) {
				__m_phasor_32.phase = 0;
				
			};
			t_sample phasor_125 = __m_phasor_32(((int)2), samples_to_seconds);
			t_sample delta_124 = __m_delta_33(phasor_125);
			int lt_123 = (delta_124 < ((int)0));
			int plusequals_121 = __m_pluseq_34.post(((int)1), (lt_123 + eq_108), 0);
			bool index_ignore_35 = ((plusequals_121 >= nob_dim) || (plusequals_121 < 0));
			// samples nob channel 1;
			t_sample sample_nob_1666 = (index_ignore_35 ? 0 : m_nob_9.read(plusequals_121, 0));
			t_sample index_nob_1667 = plusequals_121;
			t_sample add_120 = (phasor_125 + ((t_sample)0.75));
			t_sample mul_119 = (add_120 * ((t_sample)6.2831853071796));
			t_sample wrap_117 = wrap(mul_119, ((t_sample)6.2831853071796), ((int)0));
			t_sample sin_116 = sin(wrap_117);
			t_sample add_115 = (sin_116 + ((int)1));
			t_sample mul_114 = (add_115 * ((int)8));
			t_sample clamp_113 = ((mul_114 <= ((int)0)) ? ((int)0) : ((mul_114 >= ((int)1)) ? ((int)1) : mul_114));
			t_sample mul_112 = (sample_nob_1666 * clamp_113);
			t_sample clamp_99 = ((mul_112 <= min_36) ? min_36 : ((mul_112 >= ((int)1)) ? ((int)1) : mul_112));
			t_sample mul_98 = (clamp_99 * ((t_sample)0.5));
			t_sample add_97 = (mul_98 + ((int)0));
			if ((eq_40 != 0)) {
				__m_phasor_37.phase = 0;
				
			};
			t_sample phasor_57 = __m_phasor_37(((int)2), samples_to_seconds);
			t_sample delta_56 = __m_delta_38(phasor_57);
			int lt_55 = (delta_56 < ((int)0));
			int plusequals_53 = __m_pluseq_39.post(((int)1), (lt_55 + eq_40), 0);
			bool index_ignore_40 = ((plusequals_53 >= nib_dim) || (plusequals_53 < 0));
			// samples nib channel 1;
			t_sample sample_nib_42 = (index_ignore_40 ? 0 : m_nib_13.read(plusequals_53, 0));
			t_sample index_nib_43 = plusequals_53;
			t_sample add_52 = (phasor_57 + ((t_sample)0.75));
			t_sample mul_51 = (add_52 * ((t_sample)6.2831853071796));
			t_sample wrap_49 = wrap(mul_51, ((t_sample)6.2831853071796), ((int)0));
			t_sample sin_48 = sin(wrap_49);
			t_sample add_47 = (sin_48 + ((int)1));
			t_sample mul_46 = (add_47 * ((int)8));
			t_sample clamp_45 = ((mul_46 <= ((int)0)) ? ((int)0) : ((mul_46 >= ((int)1)) ? ((int)1) : mul_46));
			t_sample mul_44 = (sample_nib_42 * clamp_45);
			t_sample clamp_31 = ((mul_44 <= min_41) ? min_41 : ((mul_44 >= ((int)1)) ? ((int)1) : mul_44));
			t_sample mul_30 = (clamp_31 * ((t_sample)0.5));
			t_sample add_29 = (mul_30 + ((int)0));
			t_sample mix_3070 = (add_97 + (gt_23 * (add_29 - add_97)));
			t_sample mix_3071 = (in1 + (slide_24 * (mix_3070 - in1)));
			t_sample add_1112 = (add_2483 + mix_3071);
			t_sample out1 = add_1112;
			t_sample history_139_next_3009 = fixdenorm(switch_141);
			t_sample history_1896_next_3010 = fixdenorm(switch_1898);
			t_sample history_1899_next_3011 = fixdenorm(switch_1901);
			t_sample history_142_next_3012 = fixdenorm(switch_144);
			m_history_8 = history_131_next_133;
			m_history_7 = history_129_next_134;
			m_history_6 = history_131_next_3005;
			m_history_5 = history_129_next_3002;
			m_history_4 = history_139_next_3009;
			m_history_3 = history_1896_next_3010;
			m_history_2 = history_1899_next_3011;
			m_history_1 = history_142_next_3012;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = 0;
			(*(__out3++)) = out3;
			
		};
		return __exception;
		
	};
	inline void set_nob(void * _value) {
		m_nob_9.setbuffer(_value);
	};
	inline void set_knob1(t_param _value) {
		m_knob_10 = (_value < 0 ? 0 : (_value > 60 ? 60 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_11 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob2(t_param _value) {
		m_knob_12 = (_value < 0 ? 0 : (_value > 60 ? 60 : _value));
	};
	inline void set_nib(void * _value) {
		m_nib_13.setbuffer(_value);
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 3;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 5; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1", "out2", "led1" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_knob1(value); break;
		case 1: self->set_knob2(value); break;
		case 2: self->set_nib(ref); break;
		case 3: self->set_nob(ref); break;
		case 4: self->set_sw1(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob_10; break;
		case 1: *value = self->m_knob_12; break;
		
		
		case 4: *value = self->m_sw_11; break;
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(5 * sizeof(ParamInfo));
	self->__commonstate.numparams = 5;
	// initialize parameter 0 ("m_knob_10")
	pi = self->__commonstate.params + 0;
	pi->name = "knob1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_10;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 60;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob_12")
	pi = self->__commonstate.params + 1;
	pi->name = "knob2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_12;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 60;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_nib_13")
	pi = self->__commonstate.params + 2;
	pi->name = "nib";
	pi->paramtype = GENLIB_PARAMTYPE_SYM;
	pi->defaultvalue = 0.;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = false;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_nob_9")
	pi = self->__commonstate.params + 3;
	pi->name = "nob";
	pi->paramtype = GENLIB_PARAMTYPE_SYM;
	pi->defaultvalue = 0.;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = false;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_sw_11")
	pi = self->__commonstate.params + 4;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_11;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // MyTest::
