# UE4PropertyAccessHelpers
Utility functions for easier access to properties accessible from Blueprints but not accessible from C++.

## Usage

- Place this repository inside your's project sources.
- Add names of properties you want to use in PropertyNames.inc, like this:
```
PNAME_ENTRY(LightFalloffExponent);
PNAME_ENTRY(bUseInverseSquaredFalloff);
```
- Include PropertyNames.h in source files of your choice.
- (Optional) Add usage clause on top of your source file, like this:
```
using namespace PropertyAccessHelpers;
```
- Access properties, like this:
```
USpotLightComponent* SpotLightComponent = FindComponentByClass<USpotLightComponent>();
const float AttenuationRadius = GetPropertyValue<float, PNAME(AttenuationRadius)>(SpotLightComponent);
SetPropertyValue<bool, PNAME(CastShadows)>(SpotLightComponent, false);
```
