/*
 This file is part of CubicVR.
 
 CubicVR is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 CubicVR is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with CubicVR; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 
 
 Source (c) 2003 by Charles J. Cliffe unless otherwise specified
 To contact me, e-mail or MSN to cj@cubicproductions.com or by ICQ#7188044
 http://www.cubicproductions.com
 */

#ifndef SECTORMAP_H
#define SECTORMAP_H

#include <CubicVR/cvr_defines.h>
#include <CubicVR/SceneObject.h>
#include <CubicVR/Camera.h>
#include <CubicVR/SectorRef.h>

#include <map>
#include <set>


class SectorMap
{
	private:
		std::map<cvrIndex, std::map<cvrIndex, std::map<cvrIndex, SectorNode *, ltulong>, ltulong>, ltulong> map;
		std::map<Light *, set<SectorNode *> > static_light;
		std::map<Light *, set<SectorNode *> >::iterator static_light_i;
		std::set<SectorNode *>::iterator lightnode_i;
		std::set<SectorNode *> active_map;
		std::set<SectorNode *> last_cast;
		std::set<SceneObject *> sceneobjs;
		std::set<Light *>::iterator light_i;
		std::set<Light *> global_light;
	
		XYZ bb1, bb2;	// bounding box co-ordinates low/high
		XYZ bounds;		// XYZ representing bounds
		XYZ bbsec;		// XYZ representing single sector span
	
		Vector right,up;
		FRUSTUM frust;
		
		unsigned int divx,divy,divz;	// sector divisions
		
	public:
		SectorMap(const XYZ &bb_pt1, const XYZ &bb_pt2, double sector_size_in);

		void queryFrustum(std::set<SceneObject*> &objList, MATRIX4X4 projMatrix, MATRIX4X4 viewMatrix, float nearClip, float farClip, const int viewport[4], std::set<Light *> *lightList=NULL);
		void queryOrthoFrustum(std::set<SceneObject*> &objList, XYZ position, float width, float height, MATRIX4X4 projMatrix, MATRIX4X4 modelMatrix, float nearClip, float farClip, const int viewport[4], std::set<Light *> *lightList=NULL);
		void querySectorAABB(std::set<SceneObject*> &objList, const XYZ &aabb1_in, const XYZ &aabb2_in, std::set<Light *> *lightList=NULL);
//		void queryFrustum(std::set<SceneObject*> &objList, XYZ &position, float modelview[16], float fov, float nearclip, float farclip, float aspect, std::set<Light *> *lightList=NULL);
		void renderFrustum(Camera *cam);
		void renderOrthoFrustum(XYZ position, float width, float height, MATRIX4X4 projMatrix, MATRIX4X4 modelMatrix, float nearClip, float farClip, const int viewport[4]);
	
		void castFrustum(std::vector<SectorLoc *> &staticCast, XYZ &position, float modelview[16], float fov, float nearclip, float farclip, float aspect);
		void castSphere(std::vector<SectorLoc *> &staticCast, XYZ &position, float radius);
		void disposeStaticCast(std::vector<SectorLoc *> &staticCast);

		bool lightActivity(Light *light_in);

		void renderFrustum(MATRIX4X4 projMatrix, MATRIX4X4 modelMatrix, float nearClip, float farClip, const int viewport[4]);
	
		SectorLoc getSector(const XYZ &pt);
		void process();
		void debugDraw();
		void bind(SceneObject *sceneobj_in);		
		void unbind(SceneObject *sceneobj_in);		

		void bind(Light *light_in);		
		void unbind(Light *light_in);		

	
		static void drawBB(const XYZ &bb1, const XYZ &bb2);
};


#endif