#pragma once

class ColorRGB {
private:
    double R_;
    double G_;
    double B_;
    void Validation() {
        if (R_ > 1) R_ = 1;
        if (G_ > 1) G_ = 1;
        if (B_ > 1) B_ = 1;
        if (R_ < 0) R_ = 0;
        if (G_ < 0) G_ = 0;
        if (B_ < 0) B_ = 0;
    }
public:
    ColorRGB(double R = 0.0, double G = 0.0, double B = 0.0) {
        R_ = R;
        G_ = G;
        B_ = B;
        Validation();
    }
    ColorRGB(int R, int G, int B) {
        R_ = (double)R / 255;
        G_ = (double)G / 255;
        B_ = (double)B / 255;
        Validation();
    }
    ~ColorRGB() {}

    ColorRGB operator*= (ColorRGB color) {
        R_ *= color.R_;
        G_ *= color.G_;
        B_ *= color.B_;
        return *this;
    }
    ColorRGB operator* (ColorRGB color) {
        *this *= color;
        return *this;
    }
    ColorRGB operator*= (double val) {
        R_ *= val;
        G_ *= val;
        B_ *= val;
        Validation();
        return *this;
    }
    ColorRGB operator* (double val) {
        ColorRGB new_color = *this;
        new_color *= val;
        Validation();
        return new_color;
    }
    ColorRGB operator+= (ColorRGB color) {
        R_ += color.R_;
        G_ += color.G_;
        B_ += color.B_;
        Validation();
        return *this;
    }
    ColorRGB operator+ (ColorRGB color) {
        ColorRGB new_color = *this;
        new_color += color;
        Validation();
        return new_color;
    }
    ColorRGB operator-= (ColorRGB color) {
        R_ -= color.R_;
        G_ -= color.G_;
        B_ -= color.B_;
        Validation();
        return *this;
    }
    ColorRGB operator- (ColorRGB color) {
        ColorRGB new_color = *this;
        new_color -= color;
        Validation();
        return new_color;
    }
    bool operator== (ColorRGB color) {
        if (this->R_ == color.R_ && this->G_ == color.G_ && this->B_ == color.B_)
            return true;
        else
            return false;
    }
    bool operator!= (ColorRGB color) {
        return !(*this == color);
    }

    double GetR() { return R_; }
    double GetG() { return G_; }
    double GetB() { return B_; }
    
};