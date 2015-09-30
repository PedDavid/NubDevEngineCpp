#include "batchrenderer2d.h"

namespace engine{
	namespace graphics{

		BatchRenderer2D::BatchRenderer2D(){
			init();
		}

		BatchRenderer2D::~BatchRenderer2D(){
			delete m_IBO;
			GlCheck(glDeleteBuffers(1, &m_VBO));
			GlCheck(glDeleteVertexArrays(1, &m_VAO));
		}

		void BatchRenderer2D::init(){
			GlCheck(glGenVertexArrays(1, &m_VAO));
			GlCheck(glGenBuffers(1, &m_VBO))

			GlCheck(glBindVertexArray(m_VAO));
			GlCheck(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
			GlCheck(glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW));

			GlCheck(glEnableVertexAttribArray(SHADER_VERTEX_INDEX));
			GlCheck(glEnableVertexAttribArray(SHADER_UV_INDEX));
			GlCheck(glEnableVertexAttribArray(SHADER_TID_INDEX));
			GlCheck(glEnableVertexAttribArray(SHADER_COLOR_INDEX));

			GlCheck(glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::vertex)));
			GlCheck(glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::uv)));
			GlCheck(glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::tid)));
			GlCheck(glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::color)));

			GlCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));

			GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];
			for (int i = 0, offset = 0; i < RENDERER_INDICES_SIZE; offset += 4){
				indices[i++] = offset + 0;
				indices[i++] = offset + 1;
				indices[i++] = offset + 2;

				indices[i++] = offset + 2;
				indices[i++] = offset + 3;
				indices[i++] = offset + 0;
			}

			m_IBO = new IBO(indices, RENDERER_INDICES_SIZE);

			GlCheck(glBindVertexArray(0));
		}

		void BatchRenderer2D::begin(){
			GlCheck(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
			GlCheck(m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
		}

		void BatchRenderer2D::submit(const Renderable2D* renderable){
			const maths::vec3& position = renderable->getPosition();
			const maths::vec2& size = renderable->getSize();
			const unsigned int color = renderable->getColor();
			const std::vector<maths::vec2> &uv = renderable->getUV();
			const GLuint tid = renderable->getTID();

			float ts = 0.0f;

			if (tid > 0){
				bool found = false;
				for (int i = 0; i < m_TextureSlots.size(); i++){
					if (m_TextureSlots[i] == tid){
						ts = (float)(i + 1);
						found = true;
						break;
					}
				}
				if (!found){
					if (m_TextureSlots.size() >= RENDERER_MAX_TEXTURES){
						end();
						flush();
						begin();
					} 
					m_TextureSlots.push_back(tid);
					ts = (float)m_TextureSlots.size();
				}
			}

			maths::vec3 new_pos = *m_TransformationBack * position;

			m_Buffer->vertex = new_pos;
			m_Buffer->uv = uv[0];
			m_Buffer->tid = ts;
			m_Buffer->color = color;
			m_Buffer++;

			new_pos.y += size.y;

			m_Buffer->vertex = new_pos;
			m_Buffer->uv = uv[1];
			m_Buffer->tid = ts;
			m_Buffer->color = color;
			m_Buffer++;

			new_pos.x += size.x;

			m_Buffer->vertex = new_pos;
			m_Buffer->uv = uv[2];
			m_Buffer->tid = ts;
			m_Buffer->color = color;
			m_Buffer++;

			new_pos.y -= size.y;

			m_Buffer->vertex = new_pos;
			m_Buffer->uv = uv[3];
			m_Buffer->tid = ts;
			m_Buffer->color = color;
			m_Buffer++;

			m_IndexCount += 6;
		}

		void BatchRenderer2D::drawString(const std::string &text, const maths::vec3 &position, const Font &font, unsigned int color){
			using namespace ftgl;

			const maths::vec2 &scale = font.getScale();

			float ts = 0.0f;
			bool found = false;
			for (int i = 0; i < m_TextureSlots.size(); i++){
				if (m_TextureSlots[i] == font.getID()){
					ts = (float)(i + 1);
					found = true;
					break;
				}
			}
			if (!found){
				if (m_TextureSlots.size() >= 32){
					end();
					flush();
					begin();
				}
				m_TextureSlots.push_back(font.getID());
				ts = (float)m_TextureSlots.size();
			}

			texture_font_t* ftFont = font.getFTFont();

			float x = position.x;

			for (int i = 0; i < text.length(); i++){
				char c = text.at(i);
				texture_glyph_t *glyph = texture_font_get_glyph(ftFont, c);
				if (glyph != NULL){

					if (i > 0){
						float kerning = texture_glyph_get_kerning(glyph, text[i -1]);
						x += kerning / scale.x;
					}

					maths::vec3 current_pos(x + glyph->offset_x / scale.x, position.y + glyph->offset_y / scale.y, 0);
					maths::vec2 size(glyph->width / scale.x, -(glyph->height / scale.y));

					float u0 = glyph->s0;
					float v0 = glyph->t0;
					float u1 = glyph->s1;
					float v1 = glyph->t1;

					maths::vec3 transformated_pos = *m_TransformationBack * current_pos;

					m_Buffer->vertex = transformated_pos;
					m_Buffer->uv = maths::vec2(u0, v0);
					m_Buffer->tid = ts;
					m_Buffer->color = color;
					m_Buffer++;

					transformated_pos.y += size.y;

					m_Buffer->vertex = transformated_pos;
					m_Buffer->uv = maths::vec2(u0, v1);
					m_Buffer->tid = ts;
					m_Buffer->color = color;
					m_Buffer++;

					transformated_pos.x += size.x;

					m_Buffer->vertex = transformated_pos;
					m_Buffer->uv = maths::vec2(u1, v1);
					m_Buffer->tid = ts;
					m_Buffer->color = color;
					m_Buffer++;

					transformated_pos.y -= size.y;

					m_Buffer->vertex = transformated_pos;
					m_Buffer->uv = maths::vec2(u1, v0);
					m_Buffer->tid = ts;
					m_Buffer->color = color;
					m_Buffer++;

					m_IndexCount += 6;

					x += glyph->advance_x / scale.x;
				}
			}
		}

		void BatchRenderer2D::end(){
			GlCheck(glUnmapBuffer(GL_ARRAY_BUFFER));
			GlCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
		}

		void BatchRenderer2D::flush(){
			for (int i = 0; i < m_TextureSlots.size(); i++){
				GlCheck(glActiveTexture(GL_TEXTURE0 + i));
				GlCheck(glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]));
			}
			m_TextureSlots.clear();

			GlCheck(glBindVertexArray(m_VAO));
			m_IBO->bind();

			GlCheck(glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL));

			m_IBO->unbind();
			GlCheck(glBindVertexArray(0));

			m_IndexCount = 0;
		}


	}
}