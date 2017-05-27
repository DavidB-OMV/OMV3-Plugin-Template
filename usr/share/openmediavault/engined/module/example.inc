<?php

class OMVModuleExample extends \OMV\Engine\Module\ServiceAbstract
    implements \OMV\Engine\Notify\IListener, \OMV\Engine\Module\IServiceStatus
{
    public function getName()
    {
        return "example";
    }

    public function applyConfig()
    {
        $cmd = new \OMV\System\Process("omv-mkconf", "example");
        $cmd->setRedirect2to1();
        $cmd->execute();
    }

    public function getStatus()
    {
        $db = \OMV\Config\Database::getInstance();
        $object = $db->get("conf.service.example");
        $systemCtl = new \OMV\System\SystemCtl("example");
        return array(
            "name" => $this->getName(),
            "title" => gettext("Example"),
            "enabled" => $object->get("enable"),
            "running" => $systemCtl->isActive()
        );
    }

    public function bindListeners(\OMV\Engine\Notify\Dispatcher $dispatcher)
    {
        $dispatcher->addListener(
            OMV_NOTIFY_MODIFY,
            "org.openmediavault.conf.service.example",
            [ $this, "setDirty" ]
        );
    }
}
