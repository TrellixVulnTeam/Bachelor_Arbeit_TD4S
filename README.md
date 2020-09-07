Notes on Installation and Usage
===============================

This Appendix covers the necessary interactions to deploy and use our
project.

General Info
------------

This project has been developed under Windows 10. While usage on Linux
based systems should, in general, be possible, not all features/scripts
have been explicitly tested.

The required TensorFlow (tf) version for the python project,
found under *\[Project Root\]/NeuronalNetworks/combined\_project/*, is
*2.0.0b1* (as stated in the *requirements.txt*). Newer versions are
available, but different versions of tf are potentially incompatible,
especially concerning saved models. Therefore, to avoid problems that
might remain unnoticed, we did not upgrade the version during the course
of this project.

Installation
------------

The full code of this project is publicly available at GitHub. This also
includes the necessary version (commit hash 0a923bf) of the VTR project for
convenience (all external content is subject to its respective license,
which might be more restrictive than the license of this project).

### Code

To obtain all files necessary to use this project (except the tf C library), a
simple *clone* of the git repository is sufficient. The *master* branch
contains the full functionality.

A zip archive containing only the changes to the original VTR project is
also available. It can be patched over the appropriate version of VPR by
integrating the folder structures and replacing changed files already
present in the original project.

To use the python scripts, it is necessary to install the python modules
listed in *\[Project
Root\]/NeuronalNetworks/combined\_project/requirements.txt*.

### tf C Library

Our modified version of VPR is compiled against the tf C headers
(included in the git project), but requires the actual library at
runtime for dynamic linking.

Pre-built versions of this library are available in the official tf releases.
However, as mentioned in Chapter
<a href="#ch:tf-c-compile" data-reference-type="ref" data-reference="ch:tf-c-compile">[ch:tf-c-compile]</a>,
manual compiling of this library might be required.

On windows, the *tensorflow.dll* dynamic link library needs to be on the
Path. If it is located in the correct subfolder of the VPR project
(*\[Project Root\]/VPR\_Project/vpr/src/ml\_integration/lib/*), our
evaluation python-scripts will automatically ensure this by adding that
specific subfolder to the Path before executing VPR.

As the compiled tf C library is too large for
standard git (&gt;100), it is not included in the project repository.
Instead, it is handed in together with this thesis in a zip file.

### Trained Models, Evaluation Results and Misc Large Files

Similarly, pre-trained NNs, the placement, routing and log
files created during the evaluation, NN training data, and the remaining
files too large for GitHub are packed into zip archives and delivered
outside of the git repository.

To add all these files to the project, it is sufficient to unpack the
archives in the project root folder. The zip archives already contain
the necessary folder structure to deploy the files to their correct
locations inside the project.

Usage
-----

Once correctly installed, our modified version of VPR can be used
exactly like the original version. However, the desired mode of
operation has to be specified before compilation. This is done via a
compile-time variable at the beginning of the main source code file of
the VPR
Placer, *\[Project Root\]/VPR\_Project/vpr/src/place/place.cpp*.

### Compiling VPR

Compiling VPR usually is as easy as invoking
the CMake build system.

However, required compiler modules might be incompatible with other
installed software. We specifically needed to remove various versions of
msvc.
Furthermore, the integrated build and run utility in our IDE of choice,
JetBrains CLion, consistently fails with a cryptic linker error.
However, manually invoking *make vpr* in the root folder of the VTR Project
correctly compiles VPR in all four modes (compiler
used: cygwin gcc/g++).

### Generating Training Data

In order to generate training data, VPR has to be compiled in the
appropriate mode. Executing the VPR Placer on any circuit will now
ask the user to input a valid absolute path to store the generated data
in.

During placement, VPR will now progressively log any
temporary net placement produced, together with its BB size,
corrected HPWL cost, and cost if routed using
the Maze Router algorithm.

As this process slows the placer down dramatically, it is not practical
to wait for a whole placement attempt to finish. Instead, it can be
terminated at any point, and the samples generated up to that point will
be stored in a text file at the specified path.

### Deploying a Trained NN

Deploying a different trained NN than our already deployed
pre-trained models requires three actions. The model has to be saved in
the tf
SavedModel format and respect our interface for RNNs or CNNs.

First, the signature of the model has to be inspected using the
*saved\_model\_cli* tool included in tf to acquire the name of the entry
point used to pass data to the model. A tutorial for this process can be
found at .

Then, this entry point name has to be specified in the appropriate
compile-time variable in *\[Project
Root\]/VPR\_Project/vpr/src/ml\_integration/neural\_network.h*.

Alternatively, it is possible to change the signature definition of a
saved model to fit the predefined entry points
*serving\_default\_lstm\_renamed\_input* or
*serving\_default\_flatten\_8\_input*. An experimental implementation of
this process, described and explained in , is included in our project as
*\[Project
Root\]/NeuronalNetworks/combined\_project/fix\_model\_signatures.py*.
This script adjusts the signatures of all models created and saved in
the default locations (*\[Project
Root\]/NeuronalNetworks/combined\_project/models/\[specific
subfolder\]*) by our NN training scripts.

Finally, the saved model has to be copied to the correct location,
*\[Project
Root\]/VPR\_Project/vpr/src/ml\_integration/model\_\[type\]/*, where
*type* is either *cnn* or *rnn*.

If an entry point definition in the VPR source code has been changed,
VPR has
to be compiled again. Otherwise, no recompilation is needed, as the
appropriate model is dynamically loaded at run-time.

### Running and Evaluating VPR

We do not modify the external interface of VPR. Therefore, running and
evaluating VPR manually or with additional
tools does not require any changes once the desired mode (excluding
training data generation) has been compiled.

However, to simplify the process, we provide scripts to run the
evaluations required for model selection as well as the final evaluation
of different modes against each other. For these scripts to work, it is
required to compile VPR in each of the three modes
*reference*, *cnn integration*, and *rnn integration*. Each time, the
produced *vpr.exe* executable has to be renamed to *vpr\_reference.exe*,
*vpr\_cnn.exe*, or *vpr\_rnn.exe*, respectively. Our scripts then copy
the appropriate executable for the mode to be evaluated, giving it the
default name *vpr.exe*, before calling VPR with the arguments specific to
that evaluation run.

License
=======

This work contains content by other creators subject to their own copyrights and licenses. 

The VTR Project, located in *VPR_PROJECT/*, as well as the TensorFlow C API in *VPR_PROJECT/vpr/src/ml_integration/lib* and *VPR_PROJECT/vpr/src/ml_integration/include/tensorflow* explicitly specify their respective licenses.

When using or building upon this project all 3rd party licenses have to be respected.

This project itself with all its original content, as long as not restricted by other licenses, is subject to the MIT License.

`SPDX-License-Identifier: MIT`
