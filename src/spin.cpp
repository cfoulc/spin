#include "spin.hpp"


Plugin *plugin;

void init(rack::Plugin *p) {
	plugin = p;
	p->slug = TOSTRING(SLUG);
#ifdef VERSION
	p->version = TOSTRING(VERSION);
#endif
	p->website = "https://github.com/cfoulc/cf";
	p->manual = "https://github.com/cfoulc/cf/blob/master/README.md";


	p->addModel(modelHYPNO);

}
