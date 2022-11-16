#ifndef IPANEL_HPP
#define IPANEL_HPP

class IPanel {
  public:
    virtual void refresh() = 0;

    virtual ~IPanel() = default;
};

#endif // IPANEL_HPP
