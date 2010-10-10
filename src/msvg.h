/* msvg.h
 *
 * libmsvg, a minimal library to read and write svg files
 * Copyright (C) 2010 Mariano Alvarez Fernandez (malfer at telefonica.net)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include <stdio.h>

#define LIBMSVG_VERSION_API 0x0001

/* define id's for supported elements */
enum EID {
  EID_NOTSUPPORTED = 0,
  EID_SVG = 1,
  EID_G,
  EID_RECT,
  EID_CIRCLE,
  EID_ELLIPSE,
  EID_LINE,
  EID_POLYLINE,
  EID_POLYGON,
  EID_LAST = EID_POLYGON
};

enum EID MsvgFindElementId(const char *ename);
char * MsvgFindElementName(enum EID eid);
int MsvgIsSupSonElementId(enum EID fatherid, enum EID sonid);

/* define the rgbcolor type */

typedef int rgbcolor;

#define NO_COLOR -1

/* specific attributes for specific elements */

typedef struct _MsvgSvgAttributes {
  float vb_min_x; /* viewBox attribute */
  float vb_min_y;
  float vb_width;
  float vb_height;
  rgbcolor fill_color; /* viewport-fill attribute */
  float opacity; /* viewport-fill-opacity attribute */
} MsvgSvgAttributes;

typedef struct _MsvgRectAttributes {
  float x; /* x attribute */
  float y; /* y attribute */
  float width; /* width attribute */
  float height; /* height attribute */
  float rx; /* rx attribute */
  float ry; /* ry attribute */
} MsvgRectAttributes;

typedef struct _MsvgCircleAttributes {
  float cx; /* cx attribute */
  float cy; /* cy attribute */
  float r; /* r attribute */
} MsvgCircleAttributes;

typedef struct _MsvgEllipseAttributes {
  float cx; /* cx attribute */
  float cy; /* cy attribute */
  float rx; /* rx attribute */
  float ry; /* ry attribute */
} MsvgEllipseAttributes;

typedef struct _MsvgLineAttributes {
  float x1; /* x1 attribute */
  float y1; /* y1 attribute */
  float x2; /* x2 attribute */
  float y2; /* y2 attribute */
} MsvgLineAttributes;

typedef struct _MsvgPolylineAttributes {
  float *points; /* points attibute */
  int npoints; /* number of points */
} MsvgPolylineAttributes;

typedef struct _MsvgPolygonAttributes {
  float *points; /* points attibute */
  int npoints; /* number of points */
} MsvgPolygonAttributes;

/* generic attributes */

typedef struct _MsvgAttribute *MsvgAttributePtr;

typedef struct _MsvgAttribute {
  char *key; /* key attribute */
  char *value; /* value attribute */
  MsvgAttributePtr nattr; /* pointer to next attribute */
} MsvgAttribute;

/* element structure */

typedef struct _MsvgElement *MsvgElementPtr;

typedef struct _MsvgElement {
  enum EID eid;
  MsvgElementPtr father; /* pointer to father element */
  MsvgElementPtr psibling; /* pointer to previous sibling element */
  MsvgElementPtr nsibling; /* pointer to next sibling element */
  MsvgElementPtr fson; /* pointer to first son element */
  MsvgAttributePtr fattr; /* pointer to first generic attribute */
  union { /* specific attributes */
    MsvgSvgAttributes *psvgattr;
    MsvgRectAttributes *prectattr;
    MsvgCircleAttributes *pcircleattr;
    MsvgEllipseAttributes *pellipseattr;
    MsvgLineAttributes *plineattr;
    MsvgPolylineAttributes *ppolylineattr;
    MsvgPolygonAttributes *ppolygonattr;
  };
} MsvgElement;

int MsvgAddAttribute(MsvgElement *pelement, const char *key, const char *value);

MsvgElement *MsvgNewElement(enum EID eid, MsvgElement *father);

MsvgElement *MsvgReadSvgFile(const char *fname);

int MsvgWriteSvgFile(MsvgElement *root, const char *fname);

void MsvgPrintElementTree(FILE *f, MsvgElement *ptr, int depth);