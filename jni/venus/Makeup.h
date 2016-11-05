#ifndef VENUS_MAKEUP_H_
#define VENUS_MAKEUP_H_

#include <stdint.h>

#include <opencv2/core.hpp>

#include "venus/Region.h"

namespace venus {

class Makeup
{
public:
	enum class BlushShape
	{
		DEFAULT,
		DISK,
		OVAL,
		TRIANGLE,
		HEART,
		SEAGULL,
		
//	private:  // for internal use only
		SHAPE_COUNT
	};

private:
	static cv::Mat pack(const cv::Mat& mask, uint32_t color);

	static std::vector<cv::Point2f> createPolygon(const std::vector<cv::Point2f>& points, BlushShape shape, bool right);

	static std::vector<cv::Point2f> createHeartShape(const cv::Point2f& center, float radius, float angle = 0.0F);

	static cv::Mat createEyeShadow(cv::Mat mask[3], uint32_t color[3]/*, const int& COUNT = 3*/);

public:

	/**
	 * @param[out] dst    The destination image
	 * @param[in] src     The source image
	 * @param[in] mask    Value 0 means transparent, namely blending area, 255 means opaque.
	 * @param[in] origin  Relative origin of the <code>src</code> image on <code>dst</code> image.
	 * @param[in] amount  Blending amount in range [0, 1], 0 being no effect, 1 being fully applied.
	 */
	/**@{*/
	static void blend(cv::Mat& result, const cv::Mat& dst, const cv::Mat& src, const cv::Point2i& origin, float amount);
	static void blend(cv::Mat& result, const cv::Mat& dst, const cv::Mat& src, const cv::Mat& mask, const cv::Point2i& origin, float amount);
	/**@}*/

	/**
	 * @param[out] dst
	 * @param[in] src     The source image
	 * @param[in] points  Feature points detected from <code>src</code> image.
	 * @param[in] brow    The target makeup image, need to be RGBA format
	 * @param[in] amount  Blending amount in range [0, 1], The larger the value, the thicker/heavier the eyebrow will looks.
	 */
	static void applyBrow(cv::Mat& dst, const cv::Mat& src, const std::vector<cv::Point2f>& points, const cv::Mat& brow, float amount);

	/**
	 * @param[in] cosmetic makeup about eyes
	 *
	 * @see #applyEyeShadow
	 * @see #applyEyeLash
	 */
	static void applyEye(cv::Mat& dst, const cv::Mat& src, const std::vector<cv::Point2f>& points, const cv::Mat& cosmetic, float amount);

	/**
	 * @param[out] dst
	 * @param[in] src     The source image
	 * @param[in] points  Feature points detected from <code>src</code> image.
	 * @param[in] mask    Mask of eye lash image, archived in gray image.
	 */
	static void applyEyeLash(cv::Mat& dst, const cv::Mat& src, const std::vector<cv::Point2f>& points, const cv::Mat& mask, uint32_t color, float amount);

	/**
	 * Currently we use 3 gray image as mask, 3 colors for respected mask's primary color.
	 *
	 * @param[out] dst
	 * @param[in] src     The source image
	 * @param[in] points  Feature points detected from <code>src</code> image.
	 * @param[in] mask    Pointers of 3 masks. Note that array parameters will decay into pointers, 3 is just a hint.
	 * @param[in] color   Pointers of 3 colors.
	 * @param[in] amount  Blending amount in range [0, 1], 0 being no effect, 1 being fully applied.
	 */
	static void applyEyeShadow(cv::Mat& dst, const cv::Mat& src, const std::vector<cv::Point2f>& points, cv::Mat mask[3], uint32_t color[3], float amount);

	/**
	 * http://www.makeupforever.com/us/en-us/learn/how-to/blush-applications
	 * <a href="https://simple.wikipedia.org/wiki/Blush_(color)">Tones of blush color</a> that used for theatre makeup.
	 *
	 * @param[out] dst
	 * @param[in] src     The source image
	 * @param[in] points  Feature points detected from <code>src</code> image.
	 * @param[in] shape   Shape of blush.
	 * @param[in] color   0xAABBGGRR, RGB channel will be blush's primary color, and alpha will be premultiplied to blush.
	 * @param[in] amount  Blending amount in range [0, 1], 0 being no effect, 1 being fully applied.
	 */
	static void applyBlush(cv::Mat& dst, const cv::Mat& src, const std::vector<cv::Point2f>& points, BlushShape shape, uint32_t color, float amount);

	/**
	 * Lip gloss and lipstick can make your lips look fuller, glossier and better! See how to 
	 * <a href="http://www.wikihow.com/Apply-Lip-Color">apply lip color</a>.
	 * 
	 * @param[out] dst
	 * @param[in] src     The source image
	 * @param[in] mask    Lip mask and position.
	 * @param[in] origin  Lip position, (left, top)
	 * @param[in] color   In RGBA memory layout
	 */
	static void applyLip(cv::Mat& dst, const cv::Mat& src, const std::vector<cv::Point2f>& points, uint32_t color, float amount);

};

} /* namespace venus */
#endif /* VENUS_MAKEUP_H_ */