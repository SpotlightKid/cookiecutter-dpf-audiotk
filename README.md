cookiecutter-dpf-audiotk
========================

A [cookiecutter] project template for DISTRHO Plugin Framework ([DPF]) audio
effect plugins using the Audio Toolkit ([ATK]) DSP filter library.

Usage
-----

To create a DPF effect plugin using this template, install cookiecutter (see
the [installation instructions]) and then run:

    cookiecutter https://github.com/SpotlightKid/cookiecutter-dpf-audiotk

and enter the plugin name and other info at the prompts.

A directory named after the value you gave for `repo_name` will be created
and initialized as a git repository and DPF added as a git submodule.

Enter the directory and run `make`:

    cd mynewplugin
    make

Plugin binaries will be placed in the `bin` directory. The source code for your
plugin is in a sub-directory of the `plugins` directory named after the value
you specified for `plugin_name`. Adapt it as you see fit and run `make` again
to update your binaries. The second compilation will be much faster, because
the DPF sources have already been built.


The Structure of a Plugin
-------------------------

The ATK library provides a number of "filter" classes, which need to be
connected in a processing pipeline. Filters vary from simple operators like
gain adjustment and panning, signal generators like LFOs and various actual
audio filters for frequency spectrum manipulation. Each filter has a set of
input and output ports that connect to each other. In your plugin, you feed the
incoming sample data into the input ports of the ATK filter instances, which
are at the front of the processing pipeline, and write the data coming from the
output ports of the filter instances, which are at end of the processing
pipeline, to the output buffers. ATK provides some utility classes, which take
care of feeding the input to the processing pipeline and writing the output.

The code generated by this project template already sets up a processing
pipeline, which uses these, and in the plugin's `run` method calls the
`process` method on the pipeline, which pumps the data through it. This means,
for a simple pipeline, e.g. a delay or a filter, you just have to change the
ATK filter class instance in the middle of the processing pipeline to one (or
several in a row), which implement(s) the processing you want and and update
its (their) parameters in the `setParametervalue` method. The project
template sets up a simple pipeline for a stereo delay effect with two
parameters (delay time and dry/wet ratio) as an example, that works out of the
box.

Please see the [ATK API reference](http://doc.audio-tk.com/) documentation for
available filter classes and their parameters.


Requirements
------------

* Basic development tools (C++ compiler, make, etc.)
* Git
* [cookiecutter]
* [ATK] `devel` branch

ATK should be installed system-wide, so the compiler can find the ATK headers
and the linker can find the ATK shared libraries. If this is not the case, you
have to adapt the values of the `EXTRA_INCLUDES` and `EXTRA_LIBS` variables in
the file `Makefile.mk` in the top-level directory of the created project and
add apppropriate `-I` and `-L` options for the compiler and/or linker.

For Arch Linux systems, there is an AUR package for installing ATK from its
git repository:

https://aur.archlinux.org/packages/audiotk-git/


[cookiecutter]: https://github.com/audreyr/cookiecutter
[DPF]: https://github.com/DISTRHO/DPF
[ATK]: https://github.com/mbrucher/AudioTK
[installation instructions]: http://cookiecutter.readthedocs.org/en/latest/installation.html
