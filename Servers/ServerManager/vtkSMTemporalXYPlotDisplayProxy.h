/*=========================================================================

  Program:   ParaView
  Module:    vtkSMTemporalXYPlotDisplayProxy.h

  Copyright (c) Kitware, Inc.
  All rights reserved.
  See Copyright.txt or http://www.paraview.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkSMTemporalXYPlotDisplayProxy - Temporal plot display.

#ifndef __vtkSMTemporalXYPlotDisplayProxy_h
#define __vtkSMTemporalXYPlotDisplayProxy_h

#include "vtkSMXYPlotDisplayProxy.h"

class vtkPVDataSetAttributesInformation;
class vtkSMAnimationCueProxy;
class vtkSMTemporalXYPlotDisplayProxyInternal;

class VTK_EXPORT vtkSMTemporalXYPlotDisplayProxy : public vtkSMXYPlotDisplayProxy
{
public:
  static vtkSMTemporalXYPlotDisplayProxy* New();
  vtkTypeRevisionMacro(vtkSMTemporalXYPlotDisplayProxy, 
    vtkSMXYPlotDisplayProxy);
  void PrintSelf(ostream& os, vtkIndent indent);
  
  // Description:
  // I have this funny looking AddInput instead of a simple
  // SetInput as I want to have an InputProperty for the input (rather than
  // a proxy property). Overridden to set the input to the 
  // proxy that caches data over time.
  virtual void AddInput(vtkSMSourceProxy* input, const char*,  int );

  // Description:
  // Updates all property informations by calling UpdateInformation()
  // and populating the values. It also calls UpdateDependentDomains()
  // on all properties to make sure that domains that depend on the
  // information are updated.
  virtual void UpdatePropertyInformation();

  // Description:
  // Similar to UpdatePropertyInformation() but updates only the given property.
  // If the property does not belong to the proxy, the call is ignored.
  virtual void UpdatePropertyInformation(vtkSMProperty* prop);

  // Description:
  // Remove all the arrays selected for plotting.
  void RemoveAllPointArrayNames();
  void RemoveAllCellArrayNames();

  // Description:
  // Add an array name to be plotted.
  void AddPointArrayName(const char* arrayname);
  void AddCellArrayName(const char* arrayname);

  // Description:
  // Get/Set if the point data should be plotted, or cell data.
  // Point data is plotted when this variable is set otherwise cell data 
  // is plotted. Set by default.
  vtkSetMacro(PlotPointData, int);
  vtkGetMacro(PlotPointData, int);
 
  // Description:
  // Get/Set the animation cue (or scene) proxy that will be used to generate
  // the temporal plot.
  void SetAnimationCueProxy(vtkSMAnimationCueProxy* p);
  vtkGetObjectMacro(AnimationCueProxy, vtkSMAnimationCueProxy);

  // Description:
  // Plays the animation and generates the temporal plot. 
  // Fires vtkCommand::AnimationCueTickEvent on each iteration
  // in generation of the temporal plot. Call AbortGenerateTemporalPlot()
  // in the event handler for this event to abort generation.
  void GenerateTemporalPlot();

  // Description:
  // This method aborts the GenerateTemporalPlot() calls. Calling method 
  // has any effect only when called in the vtkCommand::AnimationCueTickEvent
  // event handler for this object.
  void AbortGenerateTemporalPlot() { this->AbortTemporalPlot = 1; }

  // Description:
  // By default, this is Off. When LockTemporalCache i off, the temporal
  // dataset that is generated by GenerateTemporalPlot() is valid
  // only until any proxy upstream is modified i.e. when any proxy upstream is
  // modified, the temporal cache will be lost. To avoid invalidation
  // of this collected temporal data, set this flag.
  vtkSetMacro(LockTemporalCache, int);
  vtkGetMacro(LockTemporalCache, int);
  vtkBooleanMacro(LockTemporalCache, int);
  
  virtual void UpdateVTKObjects();
protected:
  vtkSMTemporalXYPlotDisplayProxy();
  ~vtkSMTemporalXYPlotDisplayProxy();

  virtual void CreateVTKObjects(int numObjects);

  // Description:
  // Marks for Update. When every the upstream filters are modified,
  // we must clear the temporal cache, unless, the user locked the
  // temporal cache.
  virtual void InvalidateGeometryInternal(int useCache);
  
  // This is the caching proxy. This proxy is inserted into the pipeline 
  // only when temporal cahcing is enabled. 
  vtkSMSourceProxy* TemporalCacheProxy;

  // The Animation Cue proxy used to generate temporal plot.
  vtkSMAnimationCueProxy* AnimationCueProxy;

  void UpdateArrayInformationProperties();
  void UpdateArrayInformationProperty(const char* property,  
    vtkPVDataSetAttributesInformation* info);

  int AbortTemporalPlot;

  // When flag is set, it means that the display should plot the point data
  // else it plots cell data. By default, set to 1.
  int PlotPointData;

  int LockTemporalCache;

  int InGenerateTemporalPlot;
private:
  vtkSMTemporalXYPlotDisplayProxy(const vtkSMTemporalXYPlotDisplayProxy&); // Not implemented.
  void operator=(const vtkSMTemporalXYPlotDisplayProxy&); // Not implemented.

  vtkSMTemporalXYPlotDisplayProxyInternal* Internal;
};

#endif

