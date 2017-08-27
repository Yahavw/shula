from os.path import dirname, join
import json

zmq_ip = "127.0.0.1"            # FIXME
ZMQ_PORT = 1212
SOUNDS_DIR = join(dirname(dirname(__file__)), "TreeWav")

local_configs = None


def _validate(configs):
    for treename in configs['connect_to']:
        assert treename in configs['other_trees'], (
            "tree address undefined in 'other_trees' for {}").format(treename)


with open(join(dirname(__file__), "rpi_config.json"), 'r') as f:
    local_configs = json.load(f)
    _validate(local_configs)

TREENAME = local_configs['tree_name']

TRACKER = local_configs['tracker']

# cleanup
del dirname
del join
del json
del _validate
