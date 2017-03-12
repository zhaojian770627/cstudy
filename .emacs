(load-file "~/tools/cedet-1.1/common/cedet.el")
(load-file "~/tools/cedet-1.1/semantic/bovine/semantic-gcc.el")
(load-file "~/tools/cedet-1.1/semantic/bovine/semantic-c.el")

(global-ede-mode 1)

(add-to-list 'load-path "~/tools/ecb-2.40")
(require 'ecb)
(require 'ecb-autoloads)


(semantic-load-enable-minimum-features)
(semantic-load-enable-code-helpers)
(semantic-load-enable-guady-code-helpers)
(semantic-load-enable-excessive-code-helpers)
(semantic-load-enable-semantic-debugging-helpers)

(setq make-backup-files nil)

;;Include settings
;;(require 'semantic/bovine/semantic-gcc.el)
;;(require 'semantic/bovine/semantic-c.el)

(global-linum-mode 'linum-mode)

;;bind key
(global-set-key [f12] 'semantic-ia-fast-jump)

(defun my-cedet-hook()
(local-set-key (kbd "M-n") 'semantic-ia-complete-symbol)
)
(add-hook 'c-mode-common-hook 'my-cedet-hook)

;;ecb
(setq ecb-tip-of-the-day nil)
;;ecb key
(global-set-key [f7] 'ecb-minor-mode)
(global-set-key (kbd "C-c e m") 'ecb-maximize-window-methods)
(global-set-key (kbd "C-c e d") 'ecb-maximize-window-directories)
(global-set-key (kbd "C-c e s") 'ecb-maximize-window-sources)
(global-set-key (kbd "C-c e h") 'ecb-maximize-window-history)
(global-set-key (kbd "C-c e d") 'ecb-maximize-window-directories)
(global-set-key (kbd "C-c e r") 'ecb-restore-window-sizes)

(custom-set-variables
  ;; custom-set-variables was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 '(ecb-options-version "2.40"))
(custom-set-faces
  ;; custom-set-faces was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 )
