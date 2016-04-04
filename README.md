cookiecutter-dpf-audiotk
========================

A [cookiecutter] project template for DISTRHO Plugin Framework ([DPF]) audio
effect plugins using the Audio Toolkit ([ATK]) DSP filter library.

To create a DPF effect plugin using this template, install cookiecutter (see
the [installation instructions]) and then run:

    cookiecutter https://github.com/SpotlightKid/cookiecutter-dpf-effect

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
[AudioTK]: https://github.com/mbrucher/AudioTK
[installation instructions]: http://cookiecutter.readthedocs.org/en/latest/installation.html
