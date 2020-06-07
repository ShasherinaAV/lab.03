#include "svg.h"
#include<string>
#include<sstream>



void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg "
         << "width='" << width << "' "
         << "height='" << height << "' "
         << "viewBox='0 0 " << width << " " << height << "' "
         << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end()
{
    cout << "</svg>\n";
}

void svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='" << baseline << "' >"<< text <<"</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill)
{

    cout << "<rect x='" << x <<"' y='" << y << "' width='" << width <<"' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "' />";
}
void find_minnmaxx(const vector<size_t>&bins, size_t& minn, size_t& maxx)
{

    for (double number : bins)
    {
        if (number < minn)
        {
            minn = number;
        }
        if (number > maxx)
        {
            maxx = number;
        }
    }
}
string color_bins(const vector<size_t>&bins, size_t max_count, size_t bin)
{
    size_t minn = bins[0];
    size_t maxx = bins[0];
    find_minnmaxx(bins, minn,maxx);

    ostringstream digit;
    size_t x;


    if (bin == minn)
    {
        x = 9;
    }
    else if (bin == maxx)
    {
        x = 1;
    }
    else
    {
        x =10 - (bin * 9) / max_count;
    }
    digit << x;
    string color = digit.str();
    color = color + color + color;
    return color;
}
void
show_histogram_svg(const vector<size_t>& bins)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    double top = 0;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    const size_t MAX_VIDTH = IMAGE_WIDTH- TEXT_WIDTH;
    const size_t MAX_ASTERISK = 35;
    size_t max_count = 0;
    for (size_t count : bins)
    {
        if (count > max_count)
        {
            max_count = count;
        }
    }

    for (size_t bin: bins)
    {
        string color = color_bins(bins, max_count, bin);
        cout << color << endl;

        double bin_factor ;
        const bool scalling_needed = max_count > MAX_ASTERISK;

        if (scalling_needed)
        {
            const double koeff = (double)MAX_ASTERISK / max_count;
            bin_factor= (size_t)(bin * koeff);
        }
        else
        {
            bin_factor=bin;
        }

        const double bin_width = BLOCK_WIDTH * bin_factor;



        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "mistyrose", "#"+color);
        top += BIN_HEIGHT;
    }

    svg_end();
}
