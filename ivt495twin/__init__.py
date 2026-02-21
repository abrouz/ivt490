import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import CONF_ID

DEPENDENCIES = ["uart"]
AUTO_LOAD = ["sensor"]

ivt495twin_ns = cg.esphome_ns.namespace("ivt495twin")
Ivt495Twin = ivt495twin_ns.class_("Ivt495Twin", cg.PollingComponent, uart.UARTDevice)

# Config keys for the 36 sensors
CONF_SENSORS = [f"sensor{i}" for i in range(1, 37)]

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(Ivt495Twin),
            **{cv.Optional(f"sensor{i}"): cv.use_id(sensor.Sensor) for i in range(1, 37)},
        }
    )
    .extend(uart.UART_DEVICE_SCHEMA)
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    for i in range(1, 37):
        key = f"sensor{i}"
        if key in config:
            sens = await cg.get_variable(config[key])
            cg.add(getattr(var, f"set_sensor{i}")(sens))
