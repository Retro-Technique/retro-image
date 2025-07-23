
/**
 *
 * Retro
 *
 * CEA CNRS INRIA LOGICIEL LIBRE
 *
 * Copyright(c) 2014-2025 Retro Technique
 *
 * This software is a computer program whose purpose is to provide
 * minimalist modern C++ functionalities for 2D game development.
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

#include "pch.h"

namespace retro::image
{

#pragma region Constructors

	bitmap::bitmap() noexcept
		: m_width(0)
		, m_height(0)
	{
	}

#pragma endregion
#pragma region Operations

	void bitmap::create(std::size_t width, std::size_t height)
	{
		if (width == 0 || height == 0)
		{
			return;
		}

		m_width = width;
		m_height = height;
		m_pixels.resize(m_width * m_height * 4, color::ALPHA_TRANSPARENT);
	}

	void bitmap::load_from_file(const std::filesystem::path& path)
	{
		if (!std::filesystem::exists(path))
		{
			throw std::invalid_argument("File does not exist: " + path.string());
		}

		if (!std::filesystem::is_regular_file(path))
		{
			throw std::invalid_argument("Path is not a regular file: " + path.string());
		}

		clear();

		stbi_uc* data = stbi_load(path.string().c_str(), reinterpret_cast<int*>(&m_width), reinterpret_cast<int*>(&m_height), nullptr, STBI_rgb_alpha);
		if (!data)
		{
			throw std::runtime_error("Failed to load image: " + path.string() + " - " + stbi_failure_reason());
		}

		m_width = static_cast<std::size_t>(m_width);
		m_height = static_cast<std::size_t>(m_height);
		m_pixels.assign(data, data + (m_width * m_height * 4));

		stbi_image_free(data);
	}

	void bitmap::save_to_file(const std::filesystem::path& path) const
	{
		if (m_pixels.empty() || m_width == 0 || m_height == 0)
		{
			return;
		}

		if (!std::filesystem::exists(path))
		{
			throw std::invalid_argument("File does not exist: " + path.string());
		}

		if (!std::filesystem::is_regular_file(path))
		{
			throw std::invalid_argument("Path is not a regular file: " + path.string());
		}

		const std::string ext = path.extension().string();
		int ret = 1;

		if (ext == ".png")
		{
			ret = stbi_write_png(path.string().c_str(), static_cast<int>(m_width), static_cast<int>(m_height), 4, m_pixels.data(), static_cast<int>(m_width) * 4);
		}
		else if (ext == ".jpg" || ext == ".jpeg")
		{
			ret = stbi_write_jpg(path.string().c_str(), static_cast<int>(m_width), static_cast<int>(m_height), 4, m_pixels.data(), 100);
		}
		else if (ext == ".bmp")
		{
			ret = stbi_write_bmp(path.string().c_str(), static_cast<int>(m_width), static_cast<int>(m_height), 4, m_pixels.data());
		}

		if (ret == 0)
		{
			throw std::runtime_error("Failed to save image: " + path.string() + " - " + stbi_failure_reason());
		}
	}

	void bitmap::clear() noexcept
	{
		m_width = 0;
		m_height = 0;
		m_pixels.clear();
	}

	void bitmap::mask_from_color(const retro::image::color& color, std::uint8_t alpha) noexcept
	{
		if (m_pixels.empty() || m_width == 0 || m_height == 0)
		{
			return;
		}

		retro::image::color* pixels = reinterpret_cast<retro::image::color*>(m_pixels.data());
		for (std::size_t i = 0; i < size(); i++)
		{
			if (pixels[i].red == color.red && pixels[i].green == color.green && pixels[i].blue == color.blue)
			{
				pixels[i].alpha = alpha;
			}
		}
	}

	void bitmap::flip_vertical() noexcept
	{
		if (m_pixels.empty() || m_width == 0 || m_height == 0)
		{
			return;
		}

		const std::size_t row_size = m_width * 4;
		for (std::size_t y = 0; y < m_height / 2; ++y)
		{
			const std::size_t opposite_y = m_height - 1 - y;
			for (std::size_t x = 0; x < row_size; ++x)
			{
				std::swap(m_pixels[y * row_size + x], m_pixels[opposite_y * row_size + x]);
			}
		}
	}

	void bitmap::flip_horizontal() noexcept
	{
		if (m_pixels.empty() || m_width == 0 || m_height == 0)
		{
			return;
		}

		const std::size_t row_size = m_width * 4;
		for (std::size_t y = 0; y < m_height; ++y)
		{
			for (std::size_t x = 0; x < m_width / 2; ++x)
			{
				const std::size_t left = y * row_size + x * 4;
				const std::size_t right = y * row_size + (m_width - 1 - x) * 4;
				for (std::size_t c = 0; c < 4; ++c)
				{
					std::swap(m_pixels[left + c], m_pixels[right + c]);
				}
			}
		}
	}

#pragma endregion

}