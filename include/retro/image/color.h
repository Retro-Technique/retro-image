/**
 *
 * Retro
 *
 * CEA CNRS INRIA LOGICIEL LIBRE
 *
 * Copyright(c) 2014-2025 Retro Technique
 *
 * This software is a computer program whose purpose is to provide
 * minimalist "C with classes" functionalities.
 *
 * This software is governed by the CeCILL license under French law and
 * abiding by the rules of distribution of free software.  You can  use,
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 *
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or
 * data to be ensured and,  more generally, to use and operate it in the
 * same conditions as regards security.
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 *
 */

#pragma once

#ifndef __RETRO_IMAGE_H_INCLUDED__
#error "Do not include this file directly, include <retro/image.h> instead."
#endif

namespace retro::image
{

	struct color
	{
#pragma region Constructors

		constexpr color() noexcept;
		constexpr color(const color& other) noexcept;
		constexpr explicit color(std::uint32_t value) noexcept;
		constexpr explicit color(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = ALPHA_OPAQUE) noexcept;
		~color() = default;

#pragma endregion
#pragma region Attributes

		static constexpr const std::uint8_t ALPHA_OPAQUE = 255;
		static constexpr const std::uint8_t ALPHA_TRANSPARENT = 0;

		std::uint8_t red;
		std::uint8_t green;
		std::uint8_t blue;
		std::uint8_t alpha;

#pragma endregion
#pragma region Operations

		[[nodiscard]] constexpr bool is_opaque() const noexcept;
		[[nodiscard]] constexpr bool is_transparent() const noexcept;
		[[nodiscard]] constexpr std::uint32_t to_integer() const noexcept;
		constexpr void from_integer(std::uint32_t value) noexcept;

#pragma endregion
#pragma region Overridables
	
		[[nodiscard]] constexpr color operator+(const color& other) noexcept;
		[[nodiscard]] constexpr color operator-(const color& other) noexcept;
		[[nodiscard]] constexpr color operator*(const color& other) noexcept;
		constexpr color& operator+=(const color& other) noexcept;
		constexpr color& operator-=(const color& other) noexcept;
		constexpr color& operator*=(const color& other) noexcept;
		[[nodiscard]] constexpr bool operator==(const color& other) const noexcept;
		[[nodiscard]] constexpr bool operator!=(const color& other) const noexcept;

#pragma endregion
	};

	std::ostream& operator<<(std::ostream& stream, const color& color) noexcept;

}

#include "color.inl"