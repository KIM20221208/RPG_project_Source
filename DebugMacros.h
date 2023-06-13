#pragma once

#include "DrawDebugHelpers.h"

/**
* Debugツール。
*/

// P42.DebugSphereを生成するマクロ。
#define DRAW_SPHERE(Location) if (GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 12, FColor::Blue, true);
// P125.DebugSphereを生成するマクロ、色を選べる、かつもっと小さい（8号）、5sの存続時間。
#define DRAW_SPHERE_COLOR(Location, Color) if (GetWorld()) DrawDebugSphere(GetWorld(), Location, 8.f, 12, Color, false, 5.f);
// P49.フレームごとにDebugSphereを生成するマクロ。
#define DRAW_SPHERE_SINGLEFRAME(Location) if (GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 12, FColor::Blue, false, -1.f);
// P43.DebugLineを生成するマクロ。
#define DRAW_LINE(StartLocation, EndLocation) if (GetWorld()) DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, true, -1.f, 0, 1.f);
// P49.フレームごとにDebugLineを生成するマクロ。
#define DRAW_LINE_SINGLEFRAME(StartLocation, EndLocation) if (GetWorld()) DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.f, 0, 1.f);
// P44.DebugPointを生成するマクロ。
#define DRAW_POINT(Location) if (GetWorld()) DrawDebugPoint(GetWorld(), Location, 15.f, FColor::Red, true);
// P49.フレームごとにDebugPointを生成するマクロ。
#define DRAW_POINT_SINGLEFRAME(Location) if (GetWorld()) DrawDebugPoint(GetWorld(), Location, 15.f, FColor::Red, false, -1.f);
//P 44.DebugLinとDebugPointより、DebugVectorを生成するマクロ。
#define DRAW_VECTOR(StartLocation, EndLocation) if (GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, true, -1.f, 0, 1.f); \
		DrawDebugPoint(GetWorld(), EndLocation, 15.f, FColor::Red, true); \
	}
// P49.DebugLinとDebugPointより、フレームごとにDebugVectorを生成するマクロ。
#define DRAW_VECTOR_SINGLEFRAME(StartLocation, EndLocation) if (GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.f, 0, 1.f); \
		DrawDebugPoint(GetWorld(), EndLocation, 15.f, FColor::Red, false, -1.f); \
	}
