/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkPVLabel.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

Copyright (c) 2000-2001 Kitware Inc. 469 Clifton Corporate Parkway,
Clifton Park, NY, 12065, USA.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * Neither the name of Kitware nor the names of any contributors may be used
   to endorse or promote products derived from this software without specific 
   prior written permission.

 * Modified source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/
#include "vtkPVLabel.h"
#include "vtkObjectFactory.h"

//----------------------------------------------------------------------------
vtkPVLabel* vtkPVLabel::New()
{
  // First try to create the object from the vtkObjectFactory
  vtkObject* ret = vtkObjectFactory::CreateInstance("vtkPVLabel");
  if (ret)
    {
    return (vtkPVLabel*)ret;
    }
  // If the factory was unable to create the object, then create it here.
  return new vtkPVLabel;
}

//----------------------------------------------------------------------------
vtkPVLabel::vtkPVLabel()
{
  this->Label = vtkKWLabel::New();
  this->Label->SetParent(this);
}

//----------------------------------------------------------------------------
vtkPVLabel::~vtkPVLabel()
{
  this->Label->Delete();
  this->Label = NULL;
}

//----------------------------------------------------------------------------
void vtkPVLabel::Create(vtkKWApplication *pvApp, char *help)
{
  const char* wname;
  
  if (this->Application)
    {
    vtkErrorMacro("LabeledToggle already created");
    return;
    }

  this->SetApplication(pvApp);
  
  // create the top level
  wname = this->GetWidgetName();
  this->Script("frame %s -borderwidth 0 -relief flat", wname);
  
  // Now a label
  this->Label->Create(pvApp, "-width 18 -justify right");
  if (help)
    {
    this->Label->SetBalloonHelpString(help);
    }
  this->Script("pack %s -side left", this->Label->GetWidgetName());  
}

//----------------------------------------------------------------------------
void vtkPVLabel::Accept()
{
  this->ModifiedFlag = 0;

}

//----------------------------------------------------------------------------
void vtkPVLabel::Reset()
{
  if ( ! this->ModifiedFlag)
    {
    return;
    }

  this->ModifiedFlag = 0;

}
