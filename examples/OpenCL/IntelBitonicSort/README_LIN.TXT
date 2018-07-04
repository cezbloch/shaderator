******************************************************************************
**              Intel(R) SDK for OpenCL(tm) Applications - Samples          **
**                                 README                                   **
******************************************************************************


*****  Overview  *****

The package includes the samples that target the Intel Xeon(R) processor and
the Intel Xeon Phi(tm) coprocessor devices. The samples are designed to run on
Linux* operating systems.
The package includes the following samples:

  - Basic Device Capabilities
  - General Matrix Multiply
  - Multi-Device Basic
  - Monte Carlo Method for Stock Options Pricing

Refer to the README and sample User's Guide in the sample-specific directory
for details about each sample.

For complete list of supported operating systems and hardware, refer to the
release notes.


*****  Software Requirements  *****

To correctly build and run samples, the following software is required:

  - GNU Make utility (make)
  - GNU C++ compiler (g++)
  - Intel SDK for OpenCL Applications XE 2013 R2 and higher
  - Bash shell - to run system-level scripts in Multi-Device Basic


*****  Sample Directory Content  *****

Sample files reside in the dedicated sample directories and in the 'common'
directory in the root-level (where samples are extracted) directory.

After extracting the package contents to a directory, the directory should
contain the following:

  - common           -- directory with common utilities and helpers;
                        this functionality is used as a basic infrastructure
                        in the sample code
  - CapsBasic        -- Basic Device Capabilities Sample
  - MultiDeviceBasic -- Multi-Device Basic Sample
  - GEMM             -- General Matrix Multiply Sample
  - MonteCarlo       -- Monte Carlo Method for Stock Options Pricing Sample
  - Makefile         -- makefile for building samples
  - README.TXT       -- Readme file


*****  Building the Sample  *****

To build all samples at once, run make at the root-level sample directory:

  $ make

After successful build, sample executables appear in the corresponding
directories. For detailed information on the execution, refer to the
sample-specific documentation.


*****  Disclaimer and Legal Information *****
By using this document, in addition to any agreements you have with Intel,
you accept the terms set forth below.

You may not use or facilitate the use of this document in connection with
any infringement or other legal analysis concerning Intel products described
herein. You agree to grant Intel a non-exclusive, royalty-free license to
any patent claim thereafter drafted which includes subject matter disclosed
herein.

THESE MATERIALS ARE PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL INTEL OR ITS
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THESE
MATERIALS, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

INFORMATION IN THIS DOCUMENT IS PROVIDED IN CONNECTION WITH INTEL
PRODUCTS. NO LICENSE, EXPRESS OR IMPLIED, BY ESTOPPEL OR OTHERWISE,
TO ANY INTELLECTUAL PROPERTY RIGHTS IS GRANTED BY THIS DOCUMENT.
EXCEPT AS PROVIDED IN INTEL'S TERMS AND CONDITIONS OF SALE FOR SUCH
PRODUCTS, INTEL ASSUMES NO LIABILITY WHATSOEVER AND INTEL DISCLAIMS
ANY EXPRESS OR IMPLIED WARRANTY, RELATING TO SALE AND/OR USE OF INTEL
PRODUCTS INCLUDING LIABILITY OR WARRANTIES RELATING TO FITNESS FOR
A PARTICULAR PURPOSE, MERCHANTABILITY, OR INFRINGEMENT OF ANY PATENT,
COPYRIGHT OR OTHER INTELLECTUAL PROPERTY RIGHT.

A "Mission Critical Application" is any application in which failure
of the Intel Product could result, directly or indirectly, in personal
injury or death. SHOULD YOU PURCHASE OR USE INTEL'S PRODUCTS FOR ANY
SUCH MISSION CRITICAL APPLICATION, YOU SHALL INDEMNIFY AND HOLD INTEL
AND ITS SUBSIDIARIES, SUBCONTRACTORS AND AFFILIATES, AND THE DIRECTORS,
OFFICERS, AND EMPLOYEES OF EACH, HARMLESS AGAINST ALL CLAIMS COSTS,
DAMAGES, AND EXPENSES AND REASONABLE ATTORNEYS' FEES ARISING OUT OF,
DIRECTLY OR INDIRECTLY, ANY CLAIM OF PRODUCT LIABILITY, PERSONAL INJURY,
OR DEATH ARISING IN ANY WAY OUT OF SUCH MISSION CRITICAL APPLICATION,
WHETHER OR NOT INTEL OR ITS SUBCONTRACTOR WAS NEGLIGENT IN THE DESIGN,
MANUFACTURE, OR WARNING OF THE INTEL PRODUCT OR ANY OF ITS PARTS.

Intel may make changes to specifications and product descriptions at
any time, without notice. Designers must not rely on the absence or
characteristics of any features or instructions marked "reserved" or
"undefined". Intel reserves these for future definition and shall have
no responsibility whatsoever for conflicts or incompatibilities arising
from future changes to them. The information here is subject to change
without notice. Do not finalize a design with this information.

The products described in this document may contain design defects or
errors known as errata which may cause the product to deviate from
published specifications. Current characterized errata are available
on request.

Contact your local Intel sales office or your distributor to obtain the
latest specifications and before placing your product order.

Copies of documents which have an order number and are referenced in
this document, or other Intel literature, may be obtained
by calling 1-800-548-4725, or go to:
http://www.intel.com/design/literature.htm

Intel Corporation is the author of the Materials, and requests that all
problem reports or change requests be submitted to it directly.

Intel Xeon Phi and Xeon are trademarks of Intel Corporation in the U.S.
and/or other countries.

* Other names and brands may be claimed as the property of others.

OpenCL and the OpenCL logo are trademarks of Apple Inc. used by
permission from Khronos.

Copyright (c) 2010-2015 Intel Corporation. All rights reserved.
