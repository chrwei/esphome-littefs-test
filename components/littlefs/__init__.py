import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.const import CONF_ID

MULTI_CONF = True

CONF_ON_SETUP = "on_setup"

littlefs_ns = cg.esphome_ns.namespace("littlefs")
littlefsComponent = littlefs_ns.class_("littlefs", cg.Component)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(littlefsComponent),
            cv.Optional(CONF_ON_SETUP): automation.validate_automation(single=True),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    # Handle on_setup lambda
    if CONF_ON_SETUP in config:
        await automation.build_automation(
            var.get_connect_trigger(), [], config[CONF_ON_SETUP]
        )