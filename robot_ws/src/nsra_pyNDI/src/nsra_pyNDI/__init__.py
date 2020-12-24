"""
Mini library used to read video data from an NDI source
"""

from nsra_pyNDI.lib import lib, ffi
from nsra_pyNDI.finder import create_ndi_finder
from nsra_pyNDI.receiver import create_receiver

# for typings
from nsra_pyNDI.finder import NDIFinder, NDISource


