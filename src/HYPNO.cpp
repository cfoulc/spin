#include "spin.hpp"
#include "dsp/digital.hpp"


struct HYPNO : Module {
	enum ParamIds {
		POT2_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		NUM_INPUTS
	};
	enum OutputIds {
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};



	HYPNO() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {reset();}
	void step() override;

	void reset() override {}


};


void HYPNO::step() {

}
//////////////////////////////////////////////////////////////////////////////

struct SpinKnob : RoundKnob {

int delta =0;

	SpinKnob() {
		setSVG(SVG::load(assetPlugin(plugin, "res/spiral.svg")));
	}
	void step() override{
		dirty = true;
		RoundKnob::step();
	}
	void draw(NVGcontext *vg) override {
		
		value=delta/200.0;
		RoundKnob::draw(vg);
		delta = delta-1;
		
	}

};

struct SKnob : SpinKnob {
	SKnob(){
	}

};

//////////////////////////////////////////////////////////////////////////////

struct cache : SVGScrew {
	cache() {
		sw->setSVG(SVG::load(assetPlugin(plugin, "res/overlay.svg")));
		box.size = sw->box.size;
	}
};

struct HYPNOWidget : ModuleWidget {
	HYPNOWidget(HYPNO *module);
};

HYPNOWidget::HYPNOWidget(HYPNO *module) : ModuleWidget(module) {
	setPanel(SVG::load(assetPlugin(plugin, "res/HYPNO.svg")));

	addChild(Widget::create<ScrewSilver>(Vec(15, 0)));
	addChild(Widget::create<ScrewSilver>(Vec(box.size.x-30, 0)));
	addChild(Widget::create<ScrewSilver>(Vec(15, 365)));
	addChild(Widget::create<ScrewSilver>(Vec(box.size.x-30, 365)));

	addParam(ParamWidget::create<SKnob>(Vec(18, 20), module, HYPNO::POT2_PARAM, -INFINITY, +INFINITY, 0.0)); 
	addChild(Widget::create<cache>(Vec(10, 0)));
}

Model *modelHYPNO = Model::create<HYPNO, HYPNOWidget>("spin", "HYPNO", "HYPNO", UTILITY_TAG);
