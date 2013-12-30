// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/views/infobars/before_translate_infobar.h"

#include "base/strings/utf_string_conversions.h"
#include "chrome/browser/translate/options_menu_model.h"
#include "chrome/browser/translate/translate_infobar_delegate.h"
#include "chrome/browser/ui/views/infobars/translate_language_menu_model.h"
#include "grit/generated_resources.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/views/controls/button/label_button.h"
#include "ui/views/controls/button/menu_button.h"
#include "ui/views/controls/label.h"
#include "ui/views/controls/menu/menu_item_view.h"

BeforeTranslateInfoBar::BeforeTranslateInfoBar(
    scoped_ptr<TranslateInfoBarDelegate> delegate)
    : TranslateInfoBarBase(delegate.Pass()),
      label_1_(NULL),
      label_2_(NULL),
      language_menu_button_(NULL),
      accept_button_(NULL),
      deny_button_(NULL),
      never_translate_button_(NULL),
      always_translate_button_(NULL),
      options_menu_button_(NULL) {
}

BeforeTranslateInfoBar::~BeforeTranslateInfoBar() {
}

void BeforeTranslateInfoBar::Layout() {
  TranslateInfoBarBase::Layout();

  int available_width = std::max(0, EndX() - StartX() - ContentMinimumWidth());
  gfx::Size label_1_size = label_1_->GetPreferredSize();
  label_1_->SetBounds(StartX(), OffsetY(label_1_),
      std::min(label_1_size.width(), available_width), label_1_size.height());
  available_width = std::max(0, available_width - label_1_size.width());

  language_menu_button_->SetPosition(
      gfx::Point(label_1_->bounds().right() + kButtonInLabelSpacing,
                 OffsetY(language_menu_button_)));

  gfx::Size label_2_size = label_2_->GetPreferredSize();
  label_2_->SetBounds(
      language_menu_button_->bounds().right() + kButtonInLabelSpacing,
      OffsetY(label_2_), std::min(label_2_size.width(), available_width),
      label_2_size.height());

  accept_button_->SetPosition(
      gfx::Point(label_2_->bounds().right() + kEndOfLabelSpacing,
                 OffsetY(accept_button_)));

  deny_button_->SetPosition(
      gfx::Point(accept_button_->bounds().right() + kButtonButtonSpacing,
                 OffsetY(deny_button_)));

  if (never_translate_button_) {
    never_translate_button_->SetPosition(
        gfx::Point(deny_button_->bounds().right() + kButtonButtonSpacing,
                   OffsetY(never_translate_button_)));
  }

  if (always_translate_button_) {
    always_translate_button_->SetPosition(
        gfx::Point(deny_button_->bounds().right() + kButtonButtonSpacing,
                   OffsetY(always_translate_button_)));
  }

  options_menu_button_->SetPosition(
      gfx::Point(EndX() - options_menu_button_->width(),
                 OffsetY(options_menu_button_)));
}

void BeforeTranslateInfoBar::ViewHierarchyChanged(
    const ViewHierarchyChangedDetails& details) {
  if (!details.is_add || (details.child != this) || (label_1_ != NULL)) {
    TranslateInfoBarBase::ViewHierarchyChanged(details);
    return;
  }

  size_t offset = 0;
  base::string16 text(
      l10n_util::GetStringFUTF16(IDS_TRANSLATE_INFOBAR_BEFORE_MESSAGE,
                                 base::string16(), &offset));

  label_1_ = CreateLabel(text.substr(0, offset));
  AddChildView(label_1_);

  language_menu_button_ = CreateMenuButton(base::string16(), this);
  TranslateInfoBarDelegate* delegate = GetDelegate();
  language_menu_model_.reset(new TranslateLanguageMenuModel(
      TranslateLanguageMenuModel::ORIGINAL, delegate, this,
      language_menu_button_, false));
  AddChildView(language_menu_button_);

  label_2_ = CreateLabel(text.substr(offset));
  AddChildView(label_2_);

  accept_button_ = CreateLabelButton(this,
      l10n_util::GetStringUTF16(IDS_TRANSLATE_INFOBAR_ACCEPT), false);
  AddChildView(accept_button_);

  deny_button_ = CreateLabelButton(this,
      l10n_util::GetStringUTF16(IDS_TRANSLATE_INFOBAR_DENY), false);
  AddChildView(deny_button_);

  const base::string16& language(
      delegate->language_name_at(delegate->original_language_index()));
  if (delegate->ShouldShowNeverTranslateShortcut()) {
    DCHECK(!delegate->ShouldShowAlwaysTranslateShortcut());
    never_translate_button_ = CreateLabelButton(this,
        l10n_util::GetStringFUTF16(IDS_TRANSLATE_INFOBAR_NEVER_TRANSLATE,
                                   language), false);
    AddChildView(never_translate_button_);
  } else if (delegate->ShouldShowAlwaysTranslateShortcut()) {
    always_translate_button_ = CreateLabelButton(this,
        l10n_util::GetStringFUTF16(IDS_TRANSLATE_INFOBAR_ALWAYS_TRANSLATE,
                                   language), false);
    AddChildView(always_translate_button_);
  }

  options_menu_button_ = CreateMenuButton(
      l10n_util::GetStringUTF16(IDS_TRANSLATE_INFOBAR_OPTIONS), this);
  options_menu_model_.reset(new OptionsMenuModel(delegate));
  AddChildView(options_menu_button_);

  // This must happen after adding all other children so InfoBarView can ensure
  // the close button is the last child.
  TranslateInfoBarBase::ViewHierarchyChanged(details);

  // This must happen after adding all children because it triggers layout,
  // which assumes that particular children (e.g. the close button) have already
  // been added.
  UpdateLanguageButtonText(language_menu_button_,
      delegate->language_name_at(delegate->original_language_index()));
}

int BeforeTranslateInfoBar::ContentMinimumWidth() const {
  return
      (kButtonInLabelSpacing + language_menu_button_->width() +
          kButtonInLabelSpacing) +
      (kEndOfLabelSpacing + accept_button_->width()) +
      (kButtonButtonSpacing + deny_button_->width()) +
      (never_translate_button_ ?
          (kButtonButtonSpacing + never_translate_button_->width()) : 0) +
      (always_translate_button_ ?
          (kButtonButtonSpacing + always_translate_button_->width()) : 0) +
      (kEndOfLabelSpacing + options_menu_button_->width());
}

void BeforeTranslateInfoBar::ButtonPressed(views::Button* sender,
                                           const ui::Event& event) {
  if (!owner())
    return;  // We're closing; don't call anything, it might access the owner.
  TranslateInfoBarDelegate* delegate = GetDelegate();
  if (sender == accept_button_) {
    delegate->Translate();
  } else if (sender == deny_button_) {
    delegate->TranslationDeclined();
    RemoveSelf();
  } else if (sender == never_translate_button_) {
    delegate->NeverTranslatePageLanguage();
  } else if (sender == always_translate_button_) {
    delegate->AlwaysTranslatePageLanguage();
  } else {
    TranslateInfoBarBase::ButtonPressed(sender, event);
  }
}

void BeforeTranslateInfoBar::OnMenuButtonClicked(views::View* source,
                                                 const gfx::Point& point) {
  if (!owner())
    return;  // We're closing; don't call anything, it might access the owner.
  if (source == language_menu_button_) {
    RunMenuAt(language_menu_model_.get(), language_menu_button_,
              views::MenuItemView::TOPLEFT);
  } else {
    DCHECK_EQ(options_menu_button_, source);
    RunMenuAt(options_menu_model_.get(), options_menu_button_,
              views::MenuItemView::TOPRIGHT);
  }
}
