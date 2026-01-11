#!/bin/bash
# ROM Socket WiFi - Quick Setup Checker
# ဒီ script က WiFi testing အတွက် system ready ရှိ/မရှိ စစ်ဆေးပါတယ်

echo ""
echo "======================================================================"
echo "  ROM Socket - WiFi Setup Checker"
echo "======================================================================"
echo ""

# Color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Check counter
CHECKS_PASSED=0
CHECKS_FAILED=0

check_pass() {
    echo -e "  ${GREEN}✓${NC} $1"
    ((CHECKS_PASSED++))
}

check_fail() {
    echo -e "  ${RED}✗${NC} $1"
    ((CHECKS_FAILED++))
}

check_warning() {
    echo -e "  ${YELLOW}!${NC} $1"
}

# 1. NetworkManager စစ်ဆေးခြင်း
echo "1. Checking NetworkManager..."
if systemctl is-active --quiet NetworkManager; then
    check_pass "NetworkManager is running"
else
    check_fail "NetworkManager is NOT running"
    echo "     Fix: sudo systemctl start NetworkManager"
    echo "           sudo systemctl enable NetworkManager"
fi

# 2. nmcli command ရှိ/မရှိ
echo ""
echo "2. Checking nmcli command..."
if command -v nmcli &> /dev/null; then
    NMCLI_VERSION=$(nmcli --version | head -n1)
    check_pass "nmcli found: $NMCLI_VERSION"
else
    check_fail "nmcli not found"
    echo "     Fix: sudo apt install network-manager"
fi

# 3. WiFi device ရှိ/မရှိ
echo ""
echo "3. Checking WiFi device..."
if nmcli device status 2>/dev/null | grep -q wifi; then
    WIFI_DEVICE=$(nmcli device status | grep wifi | head -n1)
    check_pass "WiFi device found"
    echo "     $WIFI_DEVICE"
else
    check_fail "No WiFi device found"
    echo "     သင့် system မှာ WiFi hardware မရှိပါ"
fi

# 4. WiFi radio status
echo ""
echo "4. Checking WiFi radio status..."
WIFI_RADIO=$(nmcli radio wifi 2>/dev/null)
if [ "$WIFI_RADIO" == "enabled" ]; then
    check_pass "WiFi radio is enabled"
else
    check_warning "WiFi radio is disabled"
    echo "     Fix: nmcli radio wifi on"
fi

# 5. Current WiFi connection
echo ""
echo "5. Checking current WiFi connection..."
ACTIVE_WIFI=$(nmcli connection show --active 2>/dev/null | grep wifi | head -n1)
if [ -n "$ACTIVE_WIFI" ]; then
    check_pass "WiFi connected"
    echo "     $ACTIVE_WIFI"
else
    check_warning "No active WiFi connection"
    echo "     ဒါက normal ဖြစ်နိုင်ပါတယ်"
fi

# 6. User permissions
echo ""
echo "6. Checking user permissions..."
if groups | grep -qE "netdev|sudo"; then
    check_pass "User has network permissions (netdev or sudo group)"
else
    check_warning "User not in netdev or sudo group"
    echo "     Fix: sudo usermod -aG netdev $USER"
    echo "           (ပြီးရင် logout/login ပြန်လုပ်ရမယ်)"
fi

# 7. Python3 ရှိ/မရှိ (for test script)
echo ""
echo "7. Checking Python3..."
if command -v python3 &> /dev/null; then
    PYTHON_VERSION=$(python3 --version)
    check_pass "$PYTHON_VERSION found"
else
    check_fail "python3 not found"
    echo "     Fix: sudo apt install python3"
fi

# 8. ROM Socket server binary ရှိ/မရှိ
echo ""
echo "8. Checking ROM Socket server..."
if [ -f "build/rom_socket" ]; then
    check_pass "Server binary found: build/rom_socket"
else
    check_fail "Server binary not found"
    echo "     Fix: cd build && cmake .. && make"
fi

# 9. Test script ရှိ/မရှိ
echo ""
echo "9. Checking test scripts..."
if [ -f "test_wifi.py" ]; then
    check_pass "Python test script found: test_wifi.py"
else
    check_warning "test_wifi.py not found"
fi

# Summary
echo ""
echo "======================================================================"
echo "  Summary"
echo "======================================================================"
echo -e "  ${GREEN}Passed:${NC}  $CHECKS_PASSED"
echo -e "  ${RED}Failed:${NC}  $CHECKS_FAILED"
echo ""

if [ $CHECKS_FAILED -eq 0 ]; then
    echo -e "${GREEN}✓ System is ready for WiFi testing!${NC}"
    echo ""
    echo "နောက်ထပ် လုပ်ဆောင်ရမည်များ:"
    echo ""
    echo "  1. Server စတင်ခြင်း:"
    echo "     cd build && ./rom_socket"
    echo ""
    echo "  2. Test client run လုပ်ခြင်း (terminal အသစ်မှာ):"
    echo "     python3 test_wifi.py"
    echo ""
    echo "  3. သို့မဟုတ် manual testing:"
    echo "     python3 test_wifi.py <server_ip> <port>"
    echo ""
else
    echo -e "${RED}✗ Some checks failed. Please fix the issues above.${NC}"
    echo ""
fi

echo "======================================================================"
echo ""
