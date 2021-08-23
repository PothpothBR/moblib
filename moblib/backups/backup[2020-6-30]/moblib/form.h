#include "cute_c2.h"

#ifndef FORM_H
#define FORM_H


namespace COLID {
	
	class FORM {
	public:
		float *x, *y;
		c2Poly form;
		
		FORM(int points,float verts[][2]) {
			form.count = points;
			for (int i = 0;i < 3;i++) {
				form.verts[i] = c2V(verts[i][0], verts[i][1]);
			}
			c2MakePoly(&form);
		}

	};

	namespace MTH {
		bool colid(FORM *self, FORM* self2) {
			c2x s1;
			s1.p = c2V(*self->x, *self->y);
			s1.r = c2Rot(0);

			return c2PolytoPoly(&self->form, 0, &self->form, 0);
		}
	}

}


#endif