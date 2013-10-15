//incluye c headers

#include <math.h>
#include <stdlib.h>
#include <string.h>

//incluye lv2 header

#include "lv2/lv2plug.in/ns/lv2core/lv2.h"

//define url del plugin

#define PLUGIN_URI "http://lv2plug.in/plugins/eg-plugin"

// nombra los puertos
typedef enum {
	
	P_OUT = 1,
	P_IN = 0

}PortIndex;

// estructura con los datos del plugin, i.e: variables de control
typedef struct{
	
	float* input;
	float* output;

}Plugin;

//instancia del plugin

static LV2_Handle
instantiate(const LV2_Descriptor* descriptor,
				double					 rate,
				const char*				 bundle_path,
				const LV2_Feature* const* features)
{
		Plugin* plugin= (Plugin*)malloc(sizeof(Plugin));
		
		return (LV2_Handle)plugin;
}
/**esta funcion hay que llamarla siempre
el host necesita conectarse con los puertos,
a no ser que se utilice lv2:connectionOptional*/

static void
connect_port(LV2_Handle instance,
				 uint32_t port,
				 void* data)
{
		Plugin* plugin = (Plugin*)instance;
		
		switch((PortIndex)port) {
			
			case P_OUT:
				plugin->output = (float*)data;
				break;
			case P_IN:
				plugin->input = (float*)data;
				break;
		}	
}
/** si hay algo que que hacer cuando un plugin
se comporta extraño, i.e: borrar lineas de retardo, reverb, feeedbackksss :)*/

static void
activate(LV2_Handle instance)
{
	
}
/** aqui es donde se muelen todos los samples!!!*/

static void
run(LV2_Handle instance, uint32_t n_samples)
{
		const Plugin* plugin = (const Plugin*)instance;
		const float* const input = plugin->input;
		float* const output = plugin->output;
		uint32_t pos;
		for(pos=0; pos<n_samples; pos++) {
			
			// audio i/o
			output[pos] = input[pos];
		}
}
/** aqui podemos hacer cosas
cuando el plugin no se encuentre procesando
activate() se debe llamar antes de llamar a run() de nuevo*/
static void
deactivate(LV2_Handle instance)
{

}

/**terminar de limpiar*/
static void
cleanup(LV2_Handle instance)
{
	free(instance);
}

static const void*
extension_data(const char* uri)
{	
	return NULL;
}

/** core de LV2:
como se conecta el host al plugin*/

static const LV2_Descriptor descriptor ={
	
	PLUGIN_URI,
	instantiate,
	connect_port,
	activate,
	run,
	deactivate,
	cleanup,
	extension_data
};

/**el host siempre va a llamar a esta funcion
para saber como va a trabajar con el/los
plugins contenidos en el archivo*/
LV2_SYMBOL_EXPORT
const LV2_Descriptor*
lv2_descriptor(uint32_t index)
{
	switch (index) {
	case 0:
		return &descriptor;
	default:
		return NULL;
	}
}
				