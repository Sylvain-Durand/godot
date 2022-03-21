/*************************************************************************/
/*  rasterizer_gles3.h                                                   */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2022 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2022 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef RASTERIZER_OPENGL_H
#define RASTERIZER_OPENGL_H

#ifdef GLES3_ENABLED

#include "rasterizer_canvas_gles3.h"
#include "rasterizer_scene_gles3.h"
#include "rasterizer_storage_gles3.h"
#include "servers/rendering/renderer_compositor.h"
#include "storage/canvas_texture_storage.h"
#include "storage/config.h"
#include "storage/decal_atlas_storage.h"
#include "storage/material_storage.h"
#include "storage/render_target_storage.h"
#include "storage/texture_storage.h"

class RasterizerGLES3 : public RendererCompositor {
private:
	uint64_t frame = 1;
	float delta = 0;

	double time_total = 0.0;

protected:
	GLES3::Config config;
	GLES3::CanvasTextureStorage canvas_texture_storage;
	GLES3::TextureStorage texture_storage;
	GLES3::DecalAtlasStorage decal_atlas_storage;
	GLES3::MaterialStorage material_storage;
	RasterizerStorageGLES3 storage;
	RasterizerCanvasGLES3 canvas;
	RasterizerSceneGLES3 scene;

	void _blit_render_target_to_screen(RID p_render_target, DisplayServer::WindowID p_screen, const Rect2 &p_screen_rect);

public:
	RendererCanvasTextureStorage *get_canvas_texture_storage() { return &canvas_texture_storage; }
	RendererMaterialStorage *get_material_storage() { return &material_storage; }
	RendererTextureStorage *get_texture_storage() { return &texture_storage; }
	RendererDecalAtlasStorage *get_decal_atlas_storage() { return &decal_atlas_storage; }
	RendererStorage *get_storage() { return &storage; }
	RendererCanvasRender *get_canvas() { return &canvas; }
	RendererSceneRender *get_scene() { return &scene; }

	void set_boot_image(const Ref<Image> &p_image, const Color &p_color, bool p_scale, bool p_use_filter = true);

	void initialize();
	void begin_frame(double frame_step);

	void prepare_for_blitting_render_targets();
	void blit_render_targets_to_screen(DisplayServer::WindowID p_screen, const BlitToScreen *p_render_targets, int p_amount);

	void end_frame(bool p_swap_buffers);

	void finalize() {}

	static RendererCompositor *_create_current() {
		return memnew(RasterizerGLES3);
	}

	static void make_current() {
		_create_func = _create_current;
	}

	virtual bool is_low_end() const { return true; }
	uint64_t get_frame_number() const { return frame; }
	double get_frame_delta_time() const { return delta; }

	RasterizerGLES3();
	~RasterizerGLES3() {}
};

#endif // GLES3_ENABLED

#endif
