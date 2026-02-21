import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import output
from esphome.const import CONF_ID

custom_digipot_ns = cg.esphome_ns.namespace("custom_digipot")
CustomDigipotOutput = custom_digipot_ns.class_(
    "CustomDigipotOutput", cg.Component, output.FloatOutput
)

CONF_CS_PIN = "cs_pin"

CONFIG_SCHEMA = output.FLOAT_OUTPUT_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(CustomDigipotOutput),
        cv.Optional(CONF_CS_PIN, default=16): cv.int_,
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await output.register_output(var, config)
    cg.add(var.set_cs_pin(config[CONF_CS_PIN]))
