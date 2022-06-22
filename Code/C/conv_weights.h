/*
 * This file is auto-generated by gen-weights.py
 */

#pragma once

#include "definitions.h"


// Conv layer weights.
float conv_weights_old [KRN_ROWS][KRN_COLS][FILTERS]
	= {
			{
				{ -0.2894100844860077, 0.389137327671051, 1.0729731321334839, 0.7207379937171936 },
				{ 0.5813789367675781, 1.177380084991455, 1.487929105758667, 1.130525827407837 },
				{ -0.33999302983283997, -0.5757089853286743, 1.3814294338226318, -0.06569304317235947 }
			},
			{
				{ -1.2359251976013184, 1.8876452445983887, 0.5890318751335144, -0.4257088899612427 },
				{ -1.2269638776779175, -0.35385748744010925, -0.024568069726228714, 0.9493796825408936 },
				{ -0.6358994245529175, -1.5145031213760376, -0.421777606010437, 1.7579907178878784 }
			},
			{
				{ 0.315461665391922, 1.9229952096939087, -2.0710082054138184, -1.7699344158172607 },
				{ 0.5650389790534973, -0.9116737842559814, -1.4837493896484375, -1.7012189626693726 },
				{ -0.8883962631225586, -1.4511176347732544, -1.3469382524490356, 0.9352602958679199 }
			}
		};

// Conv layer biases.
float conv_biases [FILTERS] = { 0.6627478003501892, -0.9519861936569214, -0.19315217435359955, -1.1225224733352661 };
